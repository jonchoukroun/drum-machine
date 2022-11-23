#pragma once

#include <array>
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
    wxStaticBoxSizer* m_sizer { nullptr };

    struct BeatButton
    {
        bool isSet;
        wxBoxSizer* sizer;
        wxBitmapButton* button;
    };

    static constexpr int s_seqSize { 16 };
    std::array<BeatButton, s_seqSize> m_seq;

    static const wxBitmap* s_buttonOnImg;
    static const wxBitmap* s_buttonOffImg;
};
