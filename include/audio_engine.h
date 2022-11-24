#pragma once

#include <iostream>
#include <string>

#include "portaudio.h"

class AudioEngine
{
public:
    bool init();
    bool cleanup();

    void play();
    void stop();

    bool isPlaying() const { return m_playing; };

    typedef struct {
        float leftPhase;
        float rightPhase;
    } PaUserData;

private:
    PaUserData* m_data { nullptr };
    PaStream* m_stream { nullptr };

    bool m_playing { false };

    static int fillBuffer(const void* inputBuffer,
            void* outputBuffer,
            unsigned long bufferSize,
            const PaStreamCallbackTimeInfo* timeInfo,
            PaStreamCallbackFlags statusFlags,
            void* userData);

    void handlePaError(std::string, PaError);

    // Audio Settings
    // TODO: Move to class for settings change
    static constexpr int s_inputChannels { 0 };
    static constexpr int s_outputChannel { 2 };
    static constexpr double s_sampleRate { 44100.0 };
    static constexpr unsigned long s_bufferSize { 256 };
    static const PaSampleFormat s_format { paFloat32 };
};
