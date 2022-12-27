#include "snare.h"

Instrument::Instrument(double s)
    : m_sampleRate(s),
      m_ampEnv(s),
      m_pitchEnv(s)
{
    generateTable();
    m_ampEnv.setAttack(10);
    m_ampEnv.setRelease(300);
    m_ampEnv.setPeakAmp(0.8);

    m_pitchEnv.setRelease(8);
    setFreq(200.0);
}

void Instrument::setFreq(double f)
{
    m_freq = f;
    m_pitchEnv.setStartPitch(f * 20.0);
    m_pitchEnv.setEndPitch(f);
}

void Instrument::play()
{
    m_cursor = 0.0f;
    m_ampEnv.trigger();
    m_pitchEnv.trigger();
    m_playing.true;
}

void Instrument::stop()
{
    m_playing = false;
    m_cursor = 0.0f;
}