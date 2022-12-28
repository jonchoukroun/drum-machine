#include "title.h"

Title::Title(wxWindow* parent)
    : m_sizer(new wxBoxSizer(wxVERTICAL))
    , m_titleFont(new wxFont(64,
                             wxFONTFAMILY_DEFAULT,
                             wxFONTSTYLE_NORMAL,
                             wxFONTWEIGHT_EXTRABOLD,
                             false,
                             "title-font",
                             wxFONTENCODING_DEFAULT))
    , m_title(new wxStaticText(parent, wxID_ANY, APP_TITLE))
    , m_subtitleFont(new wxFont(16,
                                wxFONTFAMILY_DEFAULT,
                                wxFONTSTYLE_ITALIC,
                                wxFONTWEIGHT_NORMAL,
                                false,
                                "subtitle-font",
                                wxFONTENCODING_DEFAULT))
    , m_subtitle(new wxStaticText(parent, wxID_ANY, APP_SUBTITLE))
{
    m_title->SetFont(*m_titleFont);
    m_sizer->Add(m_title);

    m_subtitle->SetFont(*m_subtitleFont);
    m_sizer->Add(m_subtitle);
}
