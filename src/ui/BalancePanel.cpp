#include <string>

#include <wx/wx.h>

#include "ui/BalancePanel.h"
#include "ui/EventPositionPanel.h"
#include "ui/MarketPositionPanel.h"
#include "api/Api.h"

// constructor ////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

BalancePanel::BalancePanel(wxWindow* parent, wxWindowID winid)
    : wxPanel(parent, winid)
{
    Setup();
    Update();
}

// init ///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void BalancePanel::Setup()
{
    wxStaticText* lblBalance = new wxStaticText(this, wxID_ANY, "Balance:");
    lblBalanceAmount = new wxStaticText(this, wxID_ANY, "");

    wxBoxSizer* boxSizer = new wxBoxSizer(wxHORIZONTAL);

    wxSizerFlags flagsLbl = wxSizerFlags().Border(wxLEFT, 10).CenterVertical();

    boxSizer->AddStretchSpacer();
    boxSizer->Add(lblBalance, flagsLbl);
    boxSizer->Add(lblBalanceAmount, flagsLbl);

    SetSizer(boxSizer);
}

void BalancePanel::Update()
{
    try
    {
        lblBalanceAmount->SetLabelText(std::to_string(Api::GetBalance()));
    }
    catch (std::logic_error &e)
    {
        wxLogError(e.what());
    }
    catch (std::runtime_error &e)
    {
        wxLogError("Unknown error.");
        wxLogDebug(e.what());
    }
}
