#include "amp_envelope.h"

AmpEnvelope::AmpEnvelope(double s) : m_sampleRate(s) {}

void AmpEnvelope::setAttack(const double ms)
{
    m_attack = (ms / 1000.0) * m_sampleRate;
    m_attackCoef = calcCoef(m_attack, s_targetRatioA);
    m_attackBase = (1.0 + s_targetRatioA) * (1.0 - m_attackCoef);
}

void AmpEnvelope::setRelease(const double ms)
{
    m_release = (ms / 1000.0) * m_sampleRate;
    m_releaseCoef = calcCoef(m_release, s_targetRatioR);
    m_releaseBase = (0 - s_targetRatioR) * (1.0 - m_releaseCoef);
}

void AmpEnvelope::setStartAmp(const double a)
{
    m_startAmp = a;
    m_output = a;
}

void AmpEnvelope::setPeakAmp(const double a) { m_peakAmp = a; }

void AmpEnvelope::setEndAmp(const double a) { m_endAmp = a; }

double AmpEnvelope::process()
{
    if (m_isFirstSample)
    {
        m_isFirstSample = false;
        return m_output;
    }

    switch (m_state)
    {
    case State::OFF:
        break;
    case State::ATTACK:
        m_output = m_attackBase + m_output * m_attackCoef;
        if (m_output >= m_peakAmp)
        {
            m_output = m_peakAmp;
            m_state = State::RELEASE;
        }
        break;
    case State::RELEASE:
        m_output = m_releaseBase + m_output * m_releaseCoef;
        if (m_output <= m_endAmp)
        {
            m_output = m_endAmp;
            m_state = State::OFF;
        }
        break;
    }

    return m_output;
}

double AmpEnvelope::calcCoef(double rate, double targetRatio)
{
    if (rate <= 0)
    {
        return 0.0;
    }
    else
    {
        return std::exp(-std::log((1.0 + targetRatio) / targetRatio) / rate);
    }
}
