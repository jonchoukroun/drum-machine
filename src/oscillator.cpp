#include "oscillator.h"

Oscillator::Oscillator(double s)
    : m_ampEnv(s)
    , m_pitchEnv(s)
    , m_sampleRate((s))
{
    generateTable();
    // calculatePhaseAcc();
    
    m_ampEnv.setAttack(10);
    m_ampEnv.setRelease(400);
    m_ampEnv.setPeakAmp(0.8);

    m_pitchEnv.setRelease(30);
}

void Oscillator::setFreq(const double f)
{
    m_freq = f;
    m_pitchEnv.setStartPitch(f * 20.0);
    m_pitchEnv.setEndPitch(f);
    // calculatePhaseAcc();
}

void Oscillator::play()
{
    m_playing = true;
    m_ampEnv.trigger();
    m_pitchEnv.trigger();
}

void Oscillator::stop()
{
    m_playing = false;
    m_cursor = 0.0;
}

float Oscillator::getSample()
{
    if (!m_ampEnv.isOn()) return 0.0;

    double idx = m_cursor;
    if (idx >= s_tableSize) idx -= s_tableSize;

    float s = interpolate(idx);

    // m_cursor += m_phaseAcc;
    m_cursor += calcPhaseAcc();
    if (m_cursor >= s_tableSize) m_cursor -= s_tableSize;

    return s * static_cast<float>(m_ampEnv.process());
}

void Oscillator::generateTable()
{
    for (auto i = 0; i < s_tableSize; ++i)
    {
        m_table.at(i) = sin(static_cast<double>(M_PI) * 2.0 * (
                static_cast<double>(i) / static_cast<double>(s_tableSize)));
    }
}

double Oscillator::calcPhaseAcc()
{
    return static_cast<double>(s_tableSize) * m_pitchEnv.getPitch() / m_sampleRate;
}

// void Oscillator::calculatePhaseAcc()
// {
    // m_phaseAcc = static_cast<double>(s_tableSize) * m_freq / m_sampleRate;
// }

float Oscillator::interpolate(double i)
{
    const auto i0 = static_cast<int>(i);
    const auto i1 = static_cast<int>(std::ceil(i)) % m_table.size();
    const auto ilWeight = i - static_cast<double>(i0);
    return static_cast<float>(m_amp) * static_cast<float>(
            m_table.at(i1) * ilWeight + (1.0 - ilWeight) * m_table.at(i0));
}
