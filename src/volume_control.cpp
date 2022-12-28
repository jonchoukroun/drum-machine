#include "volume_control.h"

VolumeControl::VolumeControl(wxWindow* parent)
    : m_sizer((new wxStaticBoxSizer(wxVERTICAL, parent)))
    , m_volumeLabel(new wxStaticText(parent, wxID_ANY, VOLUME_LABEL))
    , m_volume(new wxSlider(parent,
                            wxID_ANY,
                            50,
                            0,
                            100,
                            wxDefaultPosition,
                            wxDefaultSize,
                            wxSL_VERTICAL))
{
    m_sizer->Add(m_volume, wxSizerFlags(0).Align(wxALIGN_CENTER));
    m_sizer->Add(m_volumeLabel,
                 wxSizerFlags(0).Align(wxALIGN_CENTER).Border(wxTOP, 20));
}
