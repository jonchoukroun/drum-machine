#pragma once

#include <wx/choice.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/window.h>

#include <string>
#include <vector>

#include "string_constants.h"
#include "voice.h"

class InstrumentPicker
{
public:
    InstrumentPicker(wxWindow*);

    wxBoxSizer* getSizer() const { return m_sizer; };

    inline wxChoice* getPicker() const { return m_picker; };

private:
    wxStaticBoxSizer* m_sizer{nullptr};
    wxStaticText* m_pickerLabel{nullptr};
    wxChoice* m_picker{nullptr};

    const std::vector<std::string> s_instruments{
        {INSTRUMENT_KICK, INSTRUMENT_SNARE, INSTRUMENT_CLOSED_HAT}};
};
