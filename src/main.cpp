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

    // Window Title
    wxBoxSizer* titleSizer = new wxBoxSizer(wxHORIZONTAL);
    wxFont* titleFont = new wxFont(64,
            wxFONTFAMILY_DEFAULT,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL,
            false,
            "title-font",
            wxFONTENCODING_DEFAULT);
    wxStaticText* title = new wxStaticText(this, wxID_ANY, "SDSx");
    title->SetFont(*titleFont);
    titleSizer->Add(title,
            wxSizerFlags(0).Align(wxALIGN_BOTTOM).Border(wxALL, 0));

    wxFont* subtitleFont = new wxFont(16,
            wxFONTFAMILY_DEFAULT,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL,
            false,
            "subtitle-font",
            wxFONTENCODING_DEFAULT);
    wxStaticText* subtitle = new wxStaticText(this,
            wxID_ANY,
            "Synthesized Drum Machine - Experiment 0.1");
    subtitle->SetFont(*subtitleFont);
    titleSizer->Add(subtitle,
            wxSizerFlags(1).Align(wxALIGN_BOTTOM).Border(wxLEFT, 20));

    mainSizer->Add(titleSizer, wxSizerFlags(0).Border(wxALL, 40));

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
    wxStaticBoxSizer* seqSizer = new wxStaticBoxSizer(wxHORIZONTAL, this);
    wxPanel* seq = new wxPanel(this,
            wxID_ANY,
            wxDefaultPosition,
            wxSize(200, 200));
    seq->SetBackgroundColour(wxColor(200, 100, 50));
    seqSizer->Add(seq, wxSizerFlags(1).Expand());

    mainSizer->Add(seqSizer,
            wxSizerFlags(0).Expand().Border(wxALL, 20));

    SetSizer(mainSizer);
}
