#pragma once

#include <array>
#include <iostream>
#include <memory>
#include <string>

#include "portaudio.h"

#include "kick.h"
#include "snare.h"
#include "voice.h"

class AudioEngine
{
public:
    bool init();
    bool cleanup();

    void play();
    void stop();

    bool isPlaying() const { return m_playing; };

    double getSampleRate() const { return s_sampleRate; };
    int getSeqSize() const { return s_seqSize; };

    int getTempo() const { return m_tempo; };
    void setTemp(const int t) { m_tempo = t; };

    static constexpr int s_seqSize{16};
    using Beats = std::array<bool, s_seqSize>;

    Beats& getBeatsFromVoice(Voice& v)
    {
        switch (v)
        {
        case Voice::Kick:
            return m_kicks;
        case Voice::Snare:
            return m_snares;
        case Voice::ClosedHats:
            return m_hats;
        default:
            std::cout << "Error! Tried to get voice from invalid instrument\n";
            return m_kicks;
        }
    }

private:
    // TODO: Move to Settings class
    // Audio Settings
    static constexpr int s_inputChannels{0};
    static constexpr int s_outputChannel{2};
    static constexpr double s_sampleRate{44100.0};
    static constexpr unsigned long s_bufferSize{256};
    static const PaSampleFormat s_format{paFloat32};

    PaStream* m_stream{nullptr};

    Beats m_kicks;
    Beats m_snares;
    Beats m_hats;

    Kick m_kick{s_sampleRate};
    Snare m_snare{s_sampleRate};

    bool m_playing{false};

    int m_tempo{80};
    float m_beatDuration{0.0f};
    float m_counter{0.0f};
    size_t m_seqCursor{0};

    static int PaStreamCallback(const void* inputBuffer,
                                void* outputBuffer,
                                unsigned long bufferSize,
                                const PaStreamCallbackTimeInfo* timeInfo,
                                PaStreamCallbackFlags statusFlags,
                                void* userData);

    void fillBuffer(float* buffer, size_t bufferSize);

    void adjustBeatDuration();

    void incrementCounters();

    void triggerInstruments();
    void clearInstruments();

    void handlePaError(std::string, PaError);

    void initBeats();
};