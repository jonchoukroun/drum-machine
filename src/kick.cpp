#include "kick.h"

Kick::Kick(double s) : m_ampEnv(s), m_pitchEnv(s), m_sampleRate((s))
{
    generateTable();

    m_ampEnv.setAttack(10);
    m_ampEnv.setRelease(300);
    m_ampEnv.setPeakAmp(0.8);

    m_pitchEnv.setRelease(8);
    setFreq(m_freq);
}

void Kick::setFreq(const double f)
{
    m_freq = f;
    m_pitchEnv.setStartPitch(f * 20.0);
    m_pitchEnv.setEndPitch(f);
}

void Kick::play()
{
    m_cursor = 0.0f;
    m_ampEnv.trigger();
    m_pitchEnv.trigger();
    m_playing = true;
}

void Kick::stop()
{
    m_playing = false;
    m_cursor = 0.0f;
}

float Kick::getSample()
{
    if (!m_ampEnv.isOn())
        return 0.0;

    double idx = m_cursor;
    if (idx >= s_tableSize)
        idx -= s_tableSize;

    float s = interpolate(idx);

    m_cursor += calcPhaseAcc();
    if (m_cursor >= s_tableSize)
        m_cursor -= s_tableSize;

    return s * static_cast<float>(m_ampEnv.process());
}

void Kick::generateTable()
{
    for (auto i = 0; i < s_tableSize; ++i)
    {
        m_table.at(i) = sin(
            static_cast<double>(M_PI) * 2.0
            * (static_cast<double>(i) / static_cast<double>(s_tableSize)));
    }
}

double Kick::calcPhaseAcc()
{
    return static_cast<double>(s_tableSize) * m_pitchEnv.getPitch()
           / m_sampleRate;
}

float Kick::interpolate(double i)
{
    const auto i0 = static_cast<int>(i);
    const auto i1 = static_cast<int>(std::ceil(i)) % m_table.size();
    const auto ilWeight = i - static_cast<double>(i0);
    return static_cast<float>(m_table.at(i1) * ilWeight
                              + (1.0 - ilWeight) * m_table.at(i0));
}
