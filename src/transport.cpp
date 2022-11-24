#include "transport.h"

Transport::Transport(wxWindow* parent, AudioEngine& engine)
    : m_engine(engine)
    , m_sizer(new wxStaticBoxSizer(wxVERTICAL, parent))
    , m_inputSizer(new wxBoxSizer(wxHORIZONTAL))
    , m_tempoInput(new wxTextCtrl(parent, wxID_ANY, "100"))
    , m_inputLabel(new wxStaticText(parent,
                wxID_ANY,
                TRANSPORT_TEMPO_INPUT_LABEL))
    , m_buttonsSizer(new wxBoxSizer(wxHORIZONTAL))
    , m_playButton(new wxButton(parent,
                wxID_ANY,
                TRANSPORT_PLAY_BUTTON))
    , m_stopButton(new wxButton(parent,
                wxID_ANY,
                TRANSPORT_STOP_BUTTON))
{
    m_inputSizer->Add(m_tempoInput,
            wxSizerFlags(1).Expand().Border(wxRIGHT, 10));
    m_inputSizer->Add(m_inputLabel,
        wxSizerFlags(0).Align(wxALIGN_CENTRE_VERTICAL));
    m_sizer->Add(m_inputSizer,
            wxSizerFlags(1).Expand().Border(wxALL, 10));

    m_buttonsSizer->Add(m_playButton,
            wxSizerFlags(0).Border(wxRIGHT, 10));
    m_buttonsSizer->Add(m_stopButton);

    m_sizer->Add(m_buttonsSizer,
            wxSizerFlags(0).Expand().Border(wxALL, 10));

    m_playButton->Bind(wxEVT_BUTTON, [=](wxCommandEvent&)
            {
                if (m_engine.isPlaying()) return;
                m_engine.play();
            });
    m_stopButton->Bind(wxEVT_BUTTON, [=](wxCommandEvent&)
            {
                if (!m_engine.isPlaying()) return;
                m_engine.stop();
            });
}
