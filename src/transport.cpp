#include "transport.h"

Transport::Transport(wxWindow* parent, AudioEngine& engine) : m_engine(engine)
{
    m_currentTempo = m_engine.getTempo();
    wxString tempo
        = wxString::Format(wxT("%d"), static_cast<int>(m_engine.getTempo()));
    m_tempoInput = new wxTextCtrl(parent, wxID_ANY, tempo);
    m_tempoInput->Bind(wxEVT_TEXT,
                       &Transport::onTempoInputChange,
                       this,
                       wxID_ANY);
    m_inputLabel
        = new wxStaticText(parent, wxID_ANY, TRANSPORT_TEMPO_INPUT_LABEL);
    m_inputSizer = new wxBoxSizer(wxHORIZONTAL);
    m_inputSizer->Add(m_tempoInput,
                      wxSizerFlags(1).Expand().Border(wxRIGHT, 10));
    m_inputSizer->Add(m_inputLabel,
                      wxSizerFlags(0).Align(wxALIGN_CENTRE_VERTICAL));

    m_playButton = new wxButton(parent, wxID_ANY, TRANSPORT_PLAY_BUTTON),
    m_playButton->Bind(wxEVT_BUTTON, &Transport::onPlayClick, this, wxID_ANY);
    m_stopButton = new wxButton(parent, wxID_ANY, TRANSPORT_STOP_BUTTON);
    m_stopButton->Disable();
    m_stopButton->Bind(wxEVT_BUTTON, &Transport::onStopClick, this, wxID_ANY);
    m_buttonsSizer = new wxBoxSizer(wxHORIZONTAL);
    m_buttonsSizer->Add(m_playButton, wxSizerFlags(0).Border(wxRIGHT, 10));
    m_buttonsSizer->Add(m_stopButton);

    m_sizer = new wxStaticBoxSizer(wxVERTICAL, parent);
    m_sizer->Add(m_inputSizer, wxSizerFlags(1).Expand().Border(wxALL, 10));
    m_sizer->Add(m_buttonsSizer, wxSizerFlags(0).Expand().Border(wxALL, 10));
}

void Transport::onTempoInputChange(wxCommandEvent& e)
{
    wxString value = m_tempoInput->GetLineText(0);
    if (!value)
        return;

    double valueDbl = 0.0;
    if (!value.ToDouble(&valueDbl))
    {
        m_tempoInput->SetValue(
            wxString::Format(wxT("%i"), m_engine.getTempo()));

        return;
    }

    int valueInt = static_cast<int>(valueDbl);
    if (valueInt <= 0)
    {
        m_tempoInput->SetValue("0");
    }
    else if (valueInt > 300)
    {
        m_tempoInput->SetValue("300");
    }
    else
    {
        m_currentTempo = valueInt;
    }
}
void Transport::onPlayClick(wxCommandEvent&)
{
    if (m_engine.isPlaying())
        return;

    if (m_currentTempo != m_engine.getTempo())
        m_engine.setTempo(m_currentTempo);

    m_engine.play();

    m_playButton->Disable();
    m_stopButton->Enable();
}

void Transport::onStopClick(wxCommandEvent&)
{
    if (!m_engine.isPlaying())
        return;

    m_engine.stop();

    m_playButton->Enable();
    m_stopButton->Disable();
}