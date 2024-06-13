#include <wx/wx.h>

#include "api/Api.hpp"
#include "ui/BalancePanel.hpp"
#include "ui/StaticCurrency.hpp"
#include "ui/event.hpp"

// constructor ////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

BalancePanel::BalancePanel(wxWindow* parent, wxWindowID winid)
    : wxPanel(parent, winid)
{
    Setup();
}

// init ///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void BalancePanel::Setup()
{
    wxStaticText* lblBalance = new wxStaticText(this, wxID_ANY, "Balance:");
    lblBalanceAmount = new StaticCurrency(this);

    wxBoxSizer* boxSizer = new wxBoxSizer(wxHORIZONTAL);

    wxSizerFlags flagsLbl = wxSizerFlags().Border(wxLEFT, 10).CenterVertical();

    boxSizer->AddStretchSpacer();
    boxSizer->Add(lblBalance, flagsLbl);
    boxSizer->Add(lblBalanceAmount, flagsLbl);

    SetSizer(boxSizer);
}

void BalancePanel::UpdateStuff()
{
    if (Api::IsLoggedIn())
    {
        try
        {
            lblBalanceAmount->SetAmount(Api::GetBalance());
        }
        catch (std::exception &e)
        {
            std::cerr << e.what() << std::endl;

            wxCommandEvent* event = new wxCommandEvent(EVT_API_ERROR);
            event->SetEventObject(this);
            event->SetString("Balance update failed!");
            QueueEvent(event);
        }
    }
    else
    {
        lblBalanceAmount->SetAmount(0);
    }
}
