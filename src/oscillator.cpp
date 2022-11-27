#include "oscillator.h"

Oscillator::Oscillator(double s)
    : m_sampleRate((s))
{
    generateTable();
    calculatePhaseAcc();
}

void Oscillator::setFreq(const float f)
{
    m_freq = f;
    calculatePhaseAcc();
}

void Oscillator::stop()
{
    m_playing = false;
    m_cursor = 0.0;
}

float Oscillator::getSample()
{
    double idx = m_cursor;
    if (idx >= s_tableSize) idx -= s_tableSize;

    m_cursor += m_phaseAcc;
    if (m_cursor >= s_tableSize) m_cursor -= s_tableSize;

    const auto i0 = static_cast<int>(idx);
    const auto i1 = static_cast<int>(std::ceil(idx)) % m_table.size();
    const auto ilWeight = idx - static_cast<float>(i0);
    return static_cast<float>(m_amp) * static_cast<float>(
            m_table.at(i1) * ilWeight + (1.0 - ilWeight) * m_table.at(i0));
}

void Oscillator::generateTable()
{
    for (auto i = 0; i < s_tableSize; ++i)
    {
        m_table.at(i) = sin(static_cast<double>(M_PI) * 2.0 * (
                static_cast<double>(i) / static_cast<double>(s_tableSize)));
    }
}

void Oscillator::calculatePhaseAcc()
{
    m_phaseAcc = static_cast<double>(s_tableSize) * m_freq / m_sampleRate;
}
