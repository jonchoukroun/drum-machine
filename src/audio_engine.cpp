#include "audio_engine.h"
#include "portaudio.h"

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
            &fillBuffer,
            &m_data);
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

int AudioEngine::fillBuffer(const void* inputBuffer,
        void* outputBuffer,
        unsigned long bufferSize,
        const PaStreamCallbackTimeInfo* timeInfo,
        PaStreamCallbackFlags statusFlags,
        void* userData)
{
    PaUserData* data = static_cast<PaUserData*>(userData);
    float* out = static_cast<float*>(outputBuffer);

    (void)inputBuffer;
    (void)timeInfo;
    (void)statusFlags;

    for (unsigned int i = 0; i < bufferSize; ++i)
    {
        *out++ = data->leftPhase * 0.5f;
        *out++ = data->rightPhase * 0.5f;
        data->leftPhase += 0.01f;
        if (data->leftPhase >= 1.0f) data->leftPhase -= 2.0f;
        data->rightPhase += 0.03f;
        if (data->rightPhase >= 1.0f) data->rightPhase -= 2.0f;
    }

    return 0;
}

void AudioEngine::handlePaError(std::string name, PaError e)
{
    std::cout << "PortAudio failed during " << name;
    std::cout << "Error: " << e << std::endl;
}
