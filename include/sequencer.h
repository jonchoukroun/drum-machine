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

#include "instrument.h"
#include "kick.h"

class Sequencer
{
public:
    Sequencer(wxWindow *, double sampleRate);

    wxStaticBoxSizer *getSizer() const { return m_sizer; };

    void setInstrument(const Instrument i);

    void updateSizer();

private:
    wxWindow *m_parent;
    wxStaticBoxSizer *m_sizer{nullptr};

    static constexpr int s_seqSize{16};
    using Voice = std::array<bool, s_seqSize>;
    Voice m_kicks;
    Voice m_snares;
    Voice m_hats;

    Instrument m_selectedInstrument{Instrument::Kick};

    inline Voice &getSelectedVoice()
    {
        switch (m_selectedInstrument)
        {
        case Instrument::Kick:
            return m_kicks;
        case Instrument::Snare:
            return m_snares;
        case Instrument::ClosedHats:
            return m_hats;
        default:
            std::cout << "Error! Tried to get voice from invalid instrument\n";
            return m_kicks;
        }
    }

    double m_sampleRate;

    wxBitmap *s_buttonOnImg;
    wxBitmap *s_buttonOffImg;
    wxSize *s_buttonSize = new wxSize(36, 36);

    void toggleBeat(wxCommandEvent &);

    void initVoices();

    wxString getButtonLabel(const size_t) const;
    wxString getButtonLabel(wxString) const;

    void initSizerButtons(Voice &);
};
