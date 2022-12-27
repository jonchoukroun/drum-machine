#pragma once

#include <wx/bitmap.h>
#include <wx/bmpbuttn.h>
#include <wx/imagpng.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/window.h>

#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>

#include "audio_engine.h"
#include "voice.h"
#include "kick.h"

class Sequencer
{
public:
    Sequencer(wxWindow *, AudioEngine &);

    wxStaticBoxSizer *getSizer() const { return m_sizer; };

    void setInstrument(const VoiceName i);

    void updateSizer();

private:
    wxWindow *m_parent;
    wxStaticBoxSizer *m_sizer{nullptr};

    AudioEngine &m_engine;

    VoiceName m_selectedInstrument{VoiceName::Kick};

    wxBitmap *s_buttonOnImg;
    wxBitmap *s_buttonOffImg;
    wxSize *s_buttonSize = new wxSize(36, 36);

    void toggleBeat(wxCommandEvent &);

    wxString getButtonLabel(const size_t) const;
    wxString getButtonLabel(wxString) const;

    void initSizerButtons(AudioEngine::Voice &);
};
