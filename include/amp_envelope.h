#pragma once

#include <cmath>
#include <iostream>

class AmpEnvelope
{
public:
    AmpEnvelope(double sampleRate);

    void setAttack(const double ms);
    void setRelease(const double ms);
    void setStartAmp(const double amp);
    void setPeakAmp(const double amp);
    void setEndAmp(const double amp);

    void trigger()
    {
        m_state = State::ATTACK;
        m_output = m_startAmp;
        m_isFirstSample = true;
    }

    bool isOn() { return m_state != State::OFF; };

    double process();

private:
    enum class State
    {
        OFF,
        ATTACK,
        RELEASE
    };
    State m_state{State::OFF};

    double m_sampleRate;

    // Rates in samples
    double m_attack{0.0};
    double m_attackCoef;
    double m_attackBase;

    double m_release{0.0};
    double m_releaseCoef;
    double m_releaseBase;

    double s_targetRatioA{0.0001};
    double s_targetRatioR{0.0001};

    // Normalized amplitude
    double m_startAmp{0.0};
    double m_peakAmp{0.0};
    double m_endAmp{0.0};

    double m_output{0.0};
    bool m_isFirstSample{false};

    double calcCoef(double rate, double targetRatio);
};
