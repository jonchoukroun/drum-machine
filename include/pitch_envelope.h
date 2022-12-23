#pragma once

#include <cmath>

class PitchEnvelope
{
public:
    PitchEnvelope(double sampleRate);

    void setRelease(const double ms);
    void setStartPitch(const double freq);
    void setEndPitch(const double freq);

    inline void trigger()
    {
        m_triggered = true;
        m_currentPitch = (m_startPitch - m_endPitch) / m_startPitch;
    }

    inline double getPitch()
    {
        if (m_triggered)
        {
            m_currentPitch = m_base + m_currentPitch * m_coef;

            if (m_endPitch + (m_currentPitch * m_startPitch) <= m_endPitch)
            {
                m_currentPitch = 0.0;
                m_triggered = false;
            }
        }

        return m_endPitch + (m_currentPitch * m_startPitch);
    }

private:
    double m_sampleRate;

    // Rate in samples
    double m_release;
    double m_coef;
    double m_base;

    double m_startPitch;
    double m_endPitch;

    // Normalized
    double m_currentPitch{1.0};

    double s_targetRatio{0.001};

    bool m_triggered{false};

    double calcCoef(double rate);
};
