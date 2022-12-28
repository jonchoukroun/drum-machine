#include "sequencer.h"

Sequencer::Sequencer(wxWindow* parent, AudioEngine& engine)
    : m_parent(parent)
    , m_sizer(new wxStaticBoxSizer(wxHORIZONTAL, parent))
    , m_engine(engine)
{
    std::cout << "Sequencer constructor called\n";
    wxImage::AddHandler(new wxPNGHandler);
    s_buttonOnImg = new wxBitmap("/Users/jonchoukroun/Developer/SoundLab/"
                                 "DrumMachine/assets/seq_button_on.png",
                                 wxBITMAP_TYPE_PNG);
    s_buttonOffImg = new wxBitmap("/Users/jonchoukroun/Developer/SoundLab/"
                                  "DrumMachine/assets/seq_button_off.png",
                                  wxBITMAP_TYPE_PNG);

    initSizerButtons(m_engine.getBeatsFromVoice(m_selectedInstrument));
}

void Sequencer::setInstrument(const Voice i)
{
    m_selectedInstrument = i;
    updateSizer();
}

void Sequencer::toggleBeat(wxCommandEvent& ev)
{
    int i = ev.GetId();
    AudioEngine::Beats& beats
        = m_engine.getBeatsFromVoice(m_selectedInstrument);
    bool isSet = beats.at(i);
    if (isSet)
    {
        beats.at(i) = false;
    }
    else
    {
        beats.at(i) = true;
    }
    updateSizer();
}

void Sequencer::updateSizer()
{
    const AudioEngine::Beats& b
        = m_engine.getBeatsFromVoice(m_selectedInstrument);
    const auto sizerCount = m_sizer->GetItemCount();
    for (auto i = 0; i != sizerCount; ++i)
    {
        assert(i != b.size());

        wxSizerItem* item = m_sizer->GetItem(i);
        wxBoxSizer* sizer = static_cast<wxBoxSizer*>(item->GetSizer());
        sizer->Clear(true);

        wxBoxSizer* newSizer = new wxBoxSizer(wxVERTICAL);

        const wxBitmap* bmp;
        if (b.at(i))
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
        button->SetLabelMarkup(getButtonLabel(i));

        newSizer->Add(button, wxSizerFlags(0).Expand());

        m_sizer->Replace(sizer, newSizer);
    }
    m_parent->Layout();
}

void Sequencer::initSizerButtons(AudioEngine::Beats& b)
{
    for (auto i = 0; i != m_engine.getSeqSize(); ++i)
    {
        wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
        const wxBitmap* bmp;
        if (b.at(i))
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
        button->SetLabelMarkup(getButtonLabel(i));

        sizer->Add(button, wxSizerFlags(0).Expand());
        m_sizer->Add(sizer);
    }
}

wxString Sequencer::getButtonLabel(const size_t i) const
{
    wxString label;
    if (i % 4 == 0)
    {
        label = wxString::Format(wxT("%d"), static_cast<int>(i / 4 + 1));
    }
    else if (i % 4 == 1)
    {
        label = wxString("e");
    }
    else if (i % 4 == 2)
    {
        label = wxString("+");
    }
    else
    {
        label = wxString("a");
    }

    return getButtonLabel(label);
}

wxString Sequencer::getButtonLabel(wxString s) const
{

    wxString* label = new wxString("<span color='white'><big>");
    wxString* end = new wxString("</big></span>");
    return *label + s + *end;
}