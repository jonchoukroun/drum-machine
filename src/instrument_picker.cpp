#include "instrument_picker.h"

InstrumentPicker::InstrumentPicker(wxWindow* parent)
    : m_sizer(new wxStaticBoxSizer(wxVERTICAL, parent))
    , m_pickerLabel(new wxStaticText(parent,
                wxID_ANY,
                INSTRUMENT_PICKER_LABEL))
    , m_picker(new wxChoice(parent, wxID_ANY))
{
    for (std::string s : s_instruments)
    {
        m_picker->Append(s);
    }

    m_sizer->Add(m_picker,
            wxSizerFlags(0).Expand().Border(wxALL, 10));
    m_sizer->Add(m_pickerLabel,
            wxSizerFlags(0).Align(wxALIGN_CENTER).Border(wxTOP, 10));
}
