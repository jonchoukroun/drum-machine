#pragma once

#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/window.h>

#include "string_constants.h"

class Transport
{
public:
    Transport(wxWindow*);

    wxBoxSizer* getSizer() const { return m_sizer; };

private:
    wxStaticBoxSizer* m_sizer { nullptr };

    wxBoxSizer* m_inputSizer { nullptr };
    wxTextCtrl* m_tempoInput { nullptr };
    wxStaticText* m_inputLabel { nullptr };

    wxBoxSizer* m_buttonsSizer { nullptr };
    wxButton* m_playButton { nullptr };
    wxButton* m_stopButton { nullptr };

    // TODO: tempo input box
};
