#pragma once

#include <wx/sizer.h>
#include <wx/slider.h>
#include <wx/stattext.h>
#include <wx/window.h>

#include "string_constants.h"

class VolumeControl
{
public:
    VolumeControl(wxWindow*);

    wxStaticBoxSizer* getSizer() const { return m_sizer; };

private:
    wxStaticBoxSizer* m_sizer { nullptr };

    wxStaticText* m_volumeLabel { nullptr };
    wxSlider* m_volume { nullptr };
};
