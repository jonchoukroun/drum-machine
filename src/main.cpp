#include "main.h"

wxIMPLEMENT_APP(DrumMachine);

bool DrumMachine::OnInit()
{
    ParentFrame* frame = new ParentFrame;
    frame->Show(true);
    return true;
}

ParentFrame::ParentFrame()
    : wxFrame(NULL, wxID_ANY, APP_TITLE)
    , m_instrumentPicker(this)
{
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(wxID_EXIT);
    Bind(wxEVT_MENU, [=](wxCommandEvent&) { Close(true); });

    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    SetMenuBar(menuBar);

    m_instrumentPicker.Show(true);
}
