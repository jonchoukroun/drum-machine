#pragma once

#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/font.h>
#include <wx/window.h>

#include "string_constants.h"

class Title
{
public:
    Title(wxWindow *);

    wxBoxSizer *getSizer() const { return m_sizer; };

private:
    wxBoxSizer *m_sizer{nullptr};

    wxFont *m_titleFont;
    wxStaticText *m_title;

    wxFont *m_subtitleFont;
    wxStaticText *m_subtitle;
};
