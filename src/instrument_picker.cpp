#include "instrument_picker.h"

InstrumentPicker::InstrumentPicker(wxWindow* parent)
    : wxPanel(parent, wxID_ANY)
    , m_picker(new wxChoice(this,
            wxID_ANY,
            wxPoint(20, 40),
            wxSize(-1, -1),
            0,
            NULL,
            0,
            wxDefaultValidator,
            wxT("Instrument Picker")))
    , m_pickerLabel(new wxStaticText(this,
                wxID_ANY,
                INSTRUMENT_PICKER_LABEL,
                wxPoint(20, 10),
                wxDefaultSize,
                0,
                wxT("Instrument Picker Label")))
{
    for (std::string s : s_instruments)
    {
        m_picker->Append(s);

    }
}

