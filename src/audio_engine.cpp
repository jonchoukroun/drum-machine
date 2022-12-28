#include "audio_engine.h"

bool AudioEngine::init()
{
    PaError initErr = Pa_Initialize();
    if (initErr != paNoError)
    {
        handlePaError("initialization", initErr);
        return false;
    }

    PaError streamErr = Pa_OpenDefaultStream(&m_stream,
                                             s_inputChannels,
                                             s_outputChannel,
                                             s_format,
                                             s_sampleRate,
                                             s_bufferSize,
                                             &PaStreamCallback,
                                             this);
    if (streamErr != paNoError)
    {
        handlePaError("open default stream", streamErr);
        return false;
    }

    adjustBeatDuration();

    initVoices();

    return true;
}

bool AudioEngine::cleanup()
{
    if (m_playing)
        stop();

    PaError closeErr = Pa_CloseStream(m_stream);
    if (closeErr != paNoError)
    {
        handlePaError("cleanup", closeErr);
        return false;
    }

    PaError termErr = Pa_Terminate();
    if (termErr != paNoError)
    {
        handlePaError("terminate", termErr);
        return false;
    }

    return true;
}

void AudioEngine::play()
{
    if (m_playing)
        return;

    m_counter = 0.0f;
    m_seqCursor = 0;
    m_playing = true;

    triggerInstruments();

    PaError err = Pa_StartStream(m_stream);
    if (err != paNoError)
    {
        handlePaError("play", err);
        return;
    }
}

void AudioEngine::stop()
{
    if (!m_playing)
        return;

    m_counter = 0.0f;
    m_seqCursor = 0;
    m_playing = false;

    m_kick.stop();

    PaError err = Pa_StopStream(m_stream);
    if (err != paNoError)
    {
        handlePaError("stop", err);
    }
}

void AudioEngine::fillBuffer(float* buffer, size_t size)
{
    for (auto i = 0; i < size; ++i)
    {
        float s = m_kick.getSample();
        *buffer++ = s;
        *buffer++ = s;

        incrementCounters();
    }
}

int AudioEngine::PaStreamCallback(const void* inputBuffer,
                                  void* outputBuffer,
                                  unsigned long bufferSize,
                                  const PaStreamCallbackTimeInfo* timeInfo,
                                  PaStreamCallbackFlags statusFlags,
                                  void* userData)
{
    AudioEngine* _this = static_cast<AudioEngine*>(userData);
    (void)inputBuffer;
    (void)timeInfo;
    (void)statusFlags;

    float* out = static_cast<float*>(outputBuffer);

    _this->fillBuffer(out, bufferSize);

    return 0;
}

void AudioEngine::adjustBeatDuration()
{
    m_beatDuration = (15.0f / static_cast<float>(m_tempo)) * s_sampleRate;
}

void AudioEngine::incrementCounters()
{
    ++m_counter;
    if (m_counter >= m_beatDuration)
    {
        m_counter = 0.0f;
        ++m_seqCursor;
        if (m_seqCursor == s_seqSize)
            m_seqCursor = 0;

        triggerInstruments();
    }
}

void AudioEngine::triggerInstruments()
{
    if (m_kicks.at(m_seqCursor))
        m_kick.play();
}

void AudioEngine::clearInstruments() { m_kick.stop(); }

void AudioEngine::handlePaError(std::string name, PaError e)
{
    std::cout << "PortAudio failed during " << name;
    std::cout << "Error: " << e << std::endl;
}

void AudioEngine::initVoices()
{
    m_kicks.fill(false);
    m_snares.fill(false);
    m_hats.fill(false);

    for (auto i = 0; i < s_seqSize; ++i)
    {
        if (i == 0 || i == 6 || i == 8)
        {
            m_kicks.at(i) = true;
            m_snares.at(i) = false;
            m_hats.at(i) = true;
        }
        else if (i == 4 || i == 12)
        {
            m_kicks.at(i) = false;
            m_snares.at(i) = true;
            m_hats.at(i) = true;
        }
        else
        {
            m_kicks.at(i) = false;
            m_snares.at(i) = false;
            m_hats.at(i) = true;
        }
    }
}