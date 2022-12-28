#include "snare.h"

Snare::Snare(double s)
    : m_drumAmpEnv(s)
    , m_snaresAmpEnv(s)
    , m_pitchEnv(s)
    , m_sampleRate((s))

{
    generateTable();

    m_rng.seed(std::chrono::steady_clock::now().time_since_epoch().count());
    m_randMax = static_cast<double>(m_rng.max());

    m_drumAmpEnv.setAttack(10);
    m_drumAmpEnv.setRelease(300);
    m_drumAmpEnv.setPeakAmp(0.8);

    m_snaresAmpEnv.setAttack(100);
    m_snaresAmpEnv.setRelease(400);
    m_snaresAmpEnv.setPeakAmp(0.8);

    m_pitchEnv.setRelease(8);
    setFreq(m_freq);
}

void Snare::setFreq(const double f)
{
    m_freq = f;
    m_pitchEnv.setStartPitch(f * 20.0);
    m_pitchEnv.setEndPitch(f);
}

void Snare::play()
{
    m_cursor = 0.0f;
    m_drumAmpEnv.trigger();
    m_snaresAmpEnv.trigger();
    m_pitchEnv.trigger();
    m_playing = true;
}

void Snare::stop()
{
    m_playing = false;
    m_cursor = 0.0f;
}

float Snare::getSample()
{
    // Snares release time is longer
    if (!m_snaresAmpEnv.isOn())
        return 0.0;

    double idx = m_cursor;
    if (idx >= s_tableSize)
        idx -= s_tableSize;

    float drum = interpolate(idx) * m_drumAmpEnv.process();

    m_cursor += calcPhaseAcc();
    if (m_cursor >= s_tableSize)
        m_cursor -= s_tableSize;

    double noise
        = (static_cast<float>(m_rng()) / m_randMax) * m_snaresAmpEnv.process();

    return 0.3f * drum + 0.7f * noise;
}

void Snare::generateTable()
{
    for (auto i = 0; i < s_tableSize; ++i)
    {
        m_table.at(i) = sin(
            static_cast<double>(M_PI) * 2.0
            * (static_cast<double>(i) / static_cast<double>(s_tableSize)));
    }
}

double Snare::calcPhaseAcc()
{
    return static_cast<double>(s_tableSize) * m_pitchEnv.getPitch()
           / m_sampleRate;
}

float Snare::interpolate(double i)
{
    const auto i0 = static_cast<int>(i);
    const auto i1 = static_cast<int>(std::ceil(i)) % m_table.size();
    const auto ilWeight = i - static_cast<double>(i0);
    return static_cast<float>(m_table.at(i1) * ilWeight
                              + (1.0 - ilWeight) * m_table.at(i0));
}
