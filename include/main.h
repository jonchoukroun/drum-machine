#include <iostream>
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "instrument_picker.h"
#include "transport.h"
#include "volume_control.h"

#include "string_constants.h"

class DrumMachine : public wxApp
{
public:
    virtual bool OnInit();
};

class ParentFrame : public wxFrame
{
public:
    ParentFrame();

private:
    InstrumentPicker m_instrumentPicker;
    Transport m_transport;
    VolumeControl m_volumeControl;
};


