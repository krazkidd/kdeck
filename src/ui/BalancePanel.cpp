#include <string>

#include <wx/wx.h>

#include "ui/BalancePanel.h"
#include "ui/EventPositionPanel.h"
#include "ui/MarketPositionPanel.h"
#include "api/Api.h"
#include "util/event.h"

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
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;

        wxCommandEvent* event = new wxCommandEvent(EVT_API_ERROR);
        event->SetString("Balance update failed!");

        event->SetEventObject(this);

        QueueEvent(event);
    }
}
