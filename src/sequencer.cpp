#include "sequencer.h"

Sequencer::Sequencer(wxWindow* parent)
    : m_parent(parent)
    , m_sizer(new wxStaticBoxSizer(wxHORIZONTAL, parent))
{
    wxImage::AddHandler(new wxPNGHandler);
    s_buttonOnImg = new wxBitmap(
            "/Users/jonchoukroun/Developer/SoundLab/DrumMachine/assets/seq_button_on.png",
            wxBITMAP_TYPE_PNG);
    s_buttonOffImg = new wxBitmap(
            "/Users/jonchoukroun/Developer/SoundLab/DrumMachine/assets/seq_button_off.png",
            wxBITMAP_TYPE_PNG);

    m_kicks.fill(false);
    updateSizer();
}

void Sequencer::toggleBeat(wxCommandEvent& ev)
{
    int i = ev.GetId();
    wxBitmapButton* b = static_cast<wxBitmapButton*>(ev.GetEventObject());
    bool isSet = m_kicks.at(i);
    if (isSet)
    {
        m_kicks.at(i) = false;
        b->SetBitmap(*s_buttonOffImg);
    }
    else
    {
        m_kicks.at(i) = true;
        b->SetBitmap(*s_buttonOnImg);
    }
}

void Sequencer::updateSizer()
{
    for (auto i = 0; i < s_seqSize; ++i)
    {
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
        const wxBitmap* bmp;
        if (m_kicks.at(i))
        {
            bmp = s_buttonOnImg;
        }
        else
        {
            bmp = s_buttonOffImg;
        }
        wxBitmapButton* button = new wxBitmapButton(m_parent,
                i,
                *bmp,
                wxDefaultPosition,
                *s_buttonSize);

        button->Bind(wxEVT_BUTTON,
                &Sequencer::toggleBeat,
                this,
                button->GetId());

        sizer->Add(button, wxSizerFlags(0).Expand());
        m_sizer->Add(sizer);
    }
}
