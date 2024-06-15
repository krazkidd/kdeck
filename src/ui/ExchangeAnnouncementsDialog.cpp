#include <wx/wx.h>

#include "api/Api.hpp"
#include "ui/ExchangeAnnouncementsDialog.hpp"
#include "ui/event.hpp"

// constructor ////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

ExchangeAnnouncementsDialog::ExchangeAnnouncementsDialog(wxWindow* parent, wxWindowID winid, const wxString &title)
    : wxDialog(parent, winid, title)
{
    Setup();
}

// init ///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void ExchangeAnnouncementsDialog::Setup()
{
    wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);

    wxSizerFlags flagsInput = wxSizerFlags().Border(wxALL, 10).Expand();

    // boxSizer->Add(TODO, flagsInput);

    wxSizer* szrButton = CreateButtonSizer(wxOK);
    if (szrButton)
    {
        boxSizer->Add(szrButton);
    }

    SetSizerAndFit(boxSizer);
}
