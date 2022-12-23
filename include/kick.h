#pragma once

#include <array>
#include <cmath>
#include <memory>

#include "portaudio.h"

#include "amp_envelope.h"
#include "pitch_envelope.h"

class Kick
{
public:
    Kick(double sampleRate);

    void setAmp(const double amplitude) { m_amp = amplitude; };
    void setFreq(const double freqquency);

    void play();
    void stop();

    float getSample();

private:
    AmpEnvelope m_ampEnv;
    PitchEnvelope m_pitchEnv;

    double m_sampleRate;

    static constexpr int s_tableSize{128};
    std::array<double, s_tableSize> m_table;

    double m_cursor;

    double m_amp{0.7};
    double m_freq{220.0};

    bool m_playing{false};

    void generateTable();
    double calcPhaseAcc();
    float interpolate(double);
};
