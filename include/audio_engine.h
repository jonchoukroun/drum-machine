#pragma once

#include <iostream>
#include <memory>
#include <string>

#include "portaudio.h"

class AudioEngine
{
public:
    bool init();
    bool cleanup();

    void play();
    void stop();

    inline bool isPlaying() const { return m_playing; };

    inline double getSampleRate() const { return s_sampleRate; };

private:
    // TODO: Move to Settings class
    // Audio Settings
    static constexpr int s_inputChannels { 0 };
    static constexpr int s_outputChannel { 2 };
    static constexpr double s_sampleRate { 44100.0 };
    static constexpr unsigned long s_bufferSize { 256 };
    static const PaSampleFormat s_format { paFloat32 };

    PaStream* m_stream { nullptr };

    bool m_playing { false };

    static int PaStreamCallback(const void* inputBuffer,
            void* outputBuffer,
            unsigned long bufferSize,
            const PaStreamCallbackTimeInfo* timeInfo,
            PaStreamCallbackFlags statusFlags,
            void* userData);

    void fillBuffer(float* buffer, size_t bufferSize);

    void handlePaError(std::string, PaError);
};
