#include "sequencer.h"

Sequencer::Sequencer(wxWindow* parent)
    : m_sizer(new wxStaticBoxSizer(wxHORIZONTAL, parent))
{
    wxImage::AddHandler(new wxPNGHandler);
    const wxBitmap* s_buttonOnImg = new wxBitmap(
            "/Users/jonchoukroun/Developer/SoundLab/DrumMachine/assets/seq_button_on.png",
            wxBITMAP_TYPE_PNG);
    const wxBitmap* s_buttonOffImg = new wxBitmap(
            "/Users/jonchoukroun/Developer/SoundLab/DrumMachine/assets/seq_button_off.png",
            wxBITMAP_TYPE_PNG);

    for (auto i = 0; i < s_seqSize; ++i)
    {
        BeatButton button;
        button.sizer = new wxBoxSizer(wxVERTICAL);
        if (i == 0 || i == 6 || i == 8 || i == 15)
        {
            button.isSet = true;
            button.button = new wxBitmapButton(parent,
                    wxID_ANY,
                    *s_buttonOnImg,
                    wxDefaultPosition,
                    wxSize(36, 36));
        }
        else
        {
            button.isSet = false;
            button.button = new wxBitmapButton(parent,
                    wxID_ANY,
                    *s_buttonOffImg,
                    wxDefaultPosition,
                    wxSize(36, 36));
        }
        m_seq.at(i) = button;

        if (i == 0)
        {
            button.sizer->Add(button.button,
                    wxSizerFlags(0).Expand());
        }
        else
        {
            button.sizer->Add(button.button,
                    wxSizerFlags(0).Expand().Border(wxLEFT, 5));
        }

        m_sizer->Add(button.sizer);
    }
}
