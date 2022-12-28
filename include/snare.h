#pragma once

#include <array>
#include <chrono>
#include <cmath>
#include <random>

#include "portaudio.h"

#include "amp_envelope.h"
#include "pitch_envelope.h"

class Snare
{
public:
    Snare(const double sampleRate);

    void setFreq(const double frequency);

    void play();
    void stop();

    float getSample();

private:
    AmpEnvelope m_drumAmpEnv;
    AmpEnvelope m_snaresAmpEnv;
    PitchEnvelope m_pitchEnv;

    std::mt19937 m_rng;
    double m_randMax;

    double m_sampleRate;

    static constexpr int s_tableSize{128};
    std::array<double, s_tableSize> m_table;

    double m_cursor;

    double m_freq{200.0};

    bool m_playing{false};

    void generateTable();
    double calcPhaseAcc();
    float interpolate(double);
};
