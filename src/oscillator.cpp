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

void Oscillator::writeSamples(float* buffer, size_t size)
{
    for (auto i = 0; i < size; ++i)
    {
        float s = getSample();
        *buffer++ = m_amp * s;
        *buffer++ = m_amp * s;
        m_cursor+= m_phaseAcc;
        if (m_cursor > s_tableSize) m_cursor -= s_tableSize;
    }
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

float Oscillator::getSample()
{
    double idx = m_cursor;
    if (m_cursor >= s_tableSize) idx -= s_tableSize;
    const auto i0 = static_cast<int>(idx);
    const auto i1 = static_cast<int>(std::ceil(idx)) % m_table.size();
    const auto ilWeight = idx - static_cast<float>(i0);
    return static_cast<float>(
            m_table.at(i1) * ilWeight + (1.0 - ilWeight) * m_table.at(i0));
}
