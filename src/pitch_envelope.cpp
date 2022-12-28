#include "pitch_envelope.h"

PitchEnvelope::PitchEnvelope(double s) : m_sampleRate(s) {}

void PitchEnvelope::setRelease(const double ms)
{
    m_release = (ms / 1000.0) * m_sampleRate;
}

void PitchEnvelope::setStartPitch(const double freq) { m_startPitch = freq; }

void PitchEnvelope::setEndPitch(const double freq)
{
    m_endPitch = freq;
    m_coef = calcCoef(m_release);
    m_base = (0.0 - s_targetRatio) * (1.0 - m_coef);
}

double PitchEnvelope::calcCoef(double rate)
{
    if (rate <= 0)
    {
        return 0.0;
    }
    else
    {
        double distance = (m_startPitch - m_endPitch) / m_startPitch;
        return std::exp(-std::log((distance + s_targetRatio) / s_targetRatio)
                        / rate);
    }
}
