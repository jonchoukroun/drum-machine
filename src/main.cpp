#include "main.h"

wxIMPLEMENT_APP(DrumMachine);

bool DrumMachine::OnInit()
{
    ParentFrame* frame = new ParentFrame;
    frame->Show(true);
    return true;
}

ParentFrame::ParentFrame()
    : wxFrame(NULL,
            wxID_ANY,
            APP_TITLE,
            wxDefaultPosition,
            wxSize(800, 600),
            wxDEFAULT_FRAME_STYLE,
            "parent-frame")
    , m_instrumentPicker(this)
    , m_sequencer(this)
    , m_title(this)
    , m_transport(this)
    , m_volumeControl(this)
{
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(wxID_EXIT);
    Bind(wxEVT_MENU, [=](wxCommandEvent&) { Close(true); });

    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    SetMenuBar(menuBar);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    // Title
    mainSizer->Add(m_title.getSizer(),
            wxSizerFlags(0).Expand().Border(wxALL, 40));

    // Control Panels
    wxBoxSizer* controlsSizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* subControlsSizer = new wxBoxSizer(wxVERTICAL);

    // controlsSizer->AddStretchSpacer();
    subControlsSizer->Add(m_instrumentPicker.getSizer(),
            wxSizerFlags(0).Expand().Border(wxBOTTOM, 10));
    subControlsSizer->Add(m_transport.getSizer(), wxSizerFlags(0));
    controlsSizer->Add(subControlsSizer,
            wxSizerFlags(0).Align(wxALIGN_CENTER).Border(wxRIGHT, 10));
    controlsSizer->Add(m_volumeControl.getSizer(),
            wxSizerFlags(0).Align(wxALIGN_BOTTOM).Border(wxLEFT, 40));

    mainSizer->Add(controlsSizer,
            wxSizerFlags(0).Expand().Border(wxLEFT | wxRIGHT, 40));

    // Sequencer
    mainSizer->Add(m_sequencer.getSizer(),
            wxSizerFlags(0)
                .Align((wxALIGN_CENTER_HORIZONTAL))
                .Border(wxALL, 40));

    SetSizer(mainSizer);
}
