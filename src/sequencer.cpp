#include "sequencer.h"

Sequencer::Sequencer(wxWindow *parent, double sampleRate)
    : m_parent(parent), m_sizer(new wxStaticBoxSizer(wxHORIZONTAL, parent)), m_sampleRate(sampleRate)
{
    std::cout << "Sequencer constructor called\n";
    wxImage::AddHandler(new wxPNGHandler);
    s_buttonOnImg = new wxBitmap(
        "/Users/jonchoukroun/Developer/SoundLab/DrumMachine/assets/seq_button_on.png",
        wxBITMAP_TYPE_PNG);
    s_buttonOffImg = new wxBitmap(
        "/Users/jonchoukroun/Developer/SoundLab/DrumMachine/assets/seq_button_off.png",
        wxBITMAP_TYPE_PNG);

    initVoices();

    initSizerButtons(getSelectedVoice());
}

void Sequencer::setInstrument(const Instrument i)
{
    m_selectedInstrument = i;
    updateSizer();
}

void Sequencer::toggleBeat(wxCommandEvent &ev)
{
    int i = ev.GetId();
    Voice &voice = getSelectedVoice();
    bool isSet = voice.at(i);
    if (isSet)
    {
        voice.at(i) = false;
    }
    else
    {
        voice.at(i) = true;
    }
    updateSizer();
}

void Sequencer::updateSizer()
{
    const Voice &v = getSelectedVoice();
    const auto sizerCount = m_sizer->GetItemCount();
    for (auto i = 0; i != sizerCount; ++i)
    {
        assert(i != v.size());

        wxSizerItem *item = m_sizer->GetItem(i);
        wxBoxSizer *sizer = static_cast<wxBoxSizer *>(item->GetSizer());
        sizer->Clear(true);

        wxBoxSizer *newSizer = new wxBoxSizer(wxVERTICAL);

        const wxBitmap *bmp;
        if (v.at(i))
        {
            bmp = s_buttonOnImg;
        }
        else
        {
            bmp = s_buttonOffImg;
        }

        wxBitmapButton *button = new wxBitmapButton(m_parent,
                                                    i, *bmp, wxDefaultPosition, *s_buttonSize);
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

void Sequencer::initSizerButtons(Voice &v)
{
    for (auto i = 0; i != s_seqSize; ++i)
    {
        wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
        const wxBitmap *bmp;
        if (v.at(i))
        {
            bmp = s_buttonOnImg;
        }
        else
        {
            bmp = s_buttonOffImg;
        }
        wxBitmapButton *button = new wxBitmapButton(m_parent,
                                                    i, *bmp, wxDefaultPosition, *s_buttonSize);
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

    wxString *label = new wxString("<span color='white'><big>");
    wxString *end = new wxString("</big></span>");
    wxString x = *label + s + *end;
    std::cout << "x: " << x << '\n';
    return x;
}

void Sequencer::initVoices()
{
    // TODO remove after using actual Voice type
    std::cout << m_sampleRate << std::endl;
    m_kicks.fill(false);
    m_snares.fill(false);
    m_hats.fill(false);

    for (auto i = 0; i < s_seqSize; ++i)
    {
        if (i == 0 || i == 6)
        {
            m_kicks.at(i) = true;
            m_snares.at(i) = false;
            m_hats.at(i) = true;
        }
        else if (i == 4 || i == 12)
        {
            m_kicks.at(i) = false;
            m_snares.at(i) = true;
            m_hats.at(i) = true;
        }
        else
        {
            m_kicks.at(i) = false;
            m_snares.at(i) = false;
            m_hats.at(i) = true;
        }
    }
}
