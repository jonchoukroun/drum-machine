#pragma once

#include <array>

#include "portaudio.h"

#include "amp_envelope.h"
#include "pitch_envelope.h"

class Instrument
{
public:
    Snare(const double sampleRate);

    void setFreq(const double freq);

    void play();
    void stop();

    float getSample();

private:
    AmpEnvelope m_ampEnv;
    PitchEnvelope m_pitchEnv;

    static_constexpr int s_tableSize{128};
    std::array<double, s_tableSize> m_table;

    double m_sampleRate;

    double m_cursor;
    double m_freq;
    double m_playing;

    void generateTable();
    double calcPhaseAcc();
    float interpolat(double);
};