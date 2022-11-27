#include "audio_engine.h"
#include "portaudio.h"
#include <cmath>
#include <memory>

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

    return true;
}

bool AudioEngine::cleanup()
{
    if (m_playing) stop();

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
    if (m_playing) return;
    m_playing = true;

    PaError err = Pa_StartStream(m_stream);
    if (err != paNoError)
    {
        handlePaError("play", err);
    }
}

void AudioEngine::stop()
{
    if (!m_playing) return;
    m_playing = false;

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
        float s = m_osc.getSample();
        *buffer++ = s;
        *buffer++ = s;
    }
}

int AudioEngine::PaStreamCallback(const void* inputBuffer,
        void* outputBuffer,
        unsigned long bufferSize,
        const PaStreamCallbackTimeInfo* timeInfo,
        PaStreamCallbackFlags statusFlags,
        void* userData)
{
    AudioEngine* _this = static_cast<AudioEngine *>(userData);
    (void)inputBuffer;
    (void)timeInfo;
    (void)statusFlags;

    float* out = static_cast<float*>(outputBuffer);

    _this->fillBuffer(out, bufferSize);

    return 0;
}

void AudioEngine::handlePaError(std::string name, PaError e)
{
    std::cout << "PortAudio failed during " << name;
    std::cout << "Error: " << e << std::endl;
}
