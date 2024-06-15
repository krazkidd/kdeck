#include <wx/wx.h>

#include "api/Api.hpp"
#include "ui/ExchangeStatusDialog.hpp"
#include "ui/event.hpp"

// constructor ////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

ExchangeStatusDialog::ExchangeStatusDialog(wxWindow* parent, wxWindowID winid, const wxString &title)
    : wxDialog(parent, winid, title)
{
    Setup();
}

// init ///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void ExchangeStatusDialog::Setup()
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
