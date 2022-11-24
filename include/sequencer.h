#pragma once

#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <wx/bitmap.h>
#include <wx/bmpbuttn.h>
#include <wx/imagpng.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/window.h>

class Sequencer
{
public:
    Sequencer(wxWindow*);

    wxStaticBoxSizer* getSizer() const { return m_sizer; };

private:
    wxWindow* m_parent;
    wxStaticBoxSizer* m_sizer { nullptr };

    static constexpr int s_seqSize { 16 };
    std::array<bool, s_seqSize> m_kicks;
    // std::array<bool, s_seqSize> m_snare;
    // std::array<bool, s_seqSize> m_closedHats;

    wxBitmap* s_buttonOnImg;
    wxBitmap* s_buttonOffImg;
    wxSize* s_buttonSize = new wxSize(36, 36);

    void updateSizer();

    void toggleBeat(wxCommandEvent&);
};
