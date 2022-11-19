#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <string>
#include <vector>

#include "string_constants.h"

class InstrumentPicker : public wxPanel
{
public:
    InstrumentPicker(wxWindow*);
private:
    wxChoice* m_picker { nullptr };

    wxStaticText* m_pickerLabel { nullptr };

    const std::vector<std::string> s_instruments{{
        INSTRUMENT_KICK,
        INSTRUMENT_SNARE,
        INSTRUMENT_CLOSED_HAT
    }};
};
