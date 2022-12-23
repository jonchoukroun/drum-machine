#include "main.h"

wxIMPLEMENT_APP(DrumMachine);

bool DrumMachine::OnInit()
{

    if (!m_engine.init())
        return false;

    ParentFrame *frame = new ParentFrame(m_engine);
    frame->Show(true);
    return true;
}

int DrumMachine::OnExit()
{
    if (!m_engine.cleanup())
    {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

ParentFrame::ParentFrame(AudioEngine &engine)
    : wxFrame(NULL, wxID_ANY, APP_TITLE, wxDefaultPosition, wxSize(800, 600),
              wxDEFAULT_FRAME_STYLE, "parent-frame"),
      m_instrumentPicker(this), m_sequencer(this, engine.getSampleRate()),
      m_title(this), m_transport(this, engine), m_volumeControl(this)

{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(wxID_EXIT);
    Bind(wxEVT_MENU, [=](wxCommandEvent &)
         { Close(true); });

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    SetMenuBar(menuBar);

    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);

    // Title
    mainSizer->Add(m_title.getSizer(),
                   wxSizerFlags(0).Expand().Border(wxALL, 40));

    // Control Panels
    wxBoxSizer *controlsSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *subControlsSizer = new wxBoxSizer(wxVERTICAL);

    // controlsSizer->AddStretchSpacer();
    subControlsSizer->Add(m_instrumentPicker.getSizer(),
                          wxSizerFlags(0).Expand().Border(wxBOTTOM, 10));
    subControlsSizer->Add(m_transport.getSizer(), wxSizerFlags(0));
    controlsSizer->Add(
        subControlsSizer,
        wxSizerFlags(0).Align(wxALIGN_CENTER).Border(wxRIGHT, 10));
    controlsSizer->Add(
        m_volumeControl.getSizer(),
        wxSizerFlags(0).Align(wxALIGN_BOTTOM).Border(wxLEFT, 40));

    mainSizer->Add(controlsSizer,
                   wxSizerFlags(0).Expand().Border(wxLEFT | wxRIGHT, 40));

    // Sequencer
    mainSizer->Add(
        m_sequencer.getSizer(),
        wxSizerFlags(0).Align((wxALIGN_CENTER_HORIZONTAL)).Border(wxALL, 40));

    // Instrument Picker
    auto *picker = m_instrumentPicker.getPicker();
    picker->Bind(wxEVT_CHOICE, &ParentFrame::OnInstrumentSelect, this);

    SetSizer(mainSizer);
}

void ParentFrame::OnInstrumentSelect(wxCommandEvent &)
{
    Instrument i = static_cast<Instrument>(
        m_instrumentPicker.getPicker()->GetCurrentSelection());
    m_sequencer.setInstrument(i);
}