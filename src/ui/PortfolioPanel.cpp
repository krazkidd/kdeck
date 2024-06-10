#include <string>

#include <wx/wx.h>

#include "api/Api.hpp"
#include "ui/PortfolioPanel.hpp"
#include "ui/EventPositionPanel.hpp"
#include "ui/MarketPositionPanel.hpp"
#include "util/event.hpp"

// constructor ////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

PortfolioPanel::PortfolioPanel(wxWindow* parent, wxWindowID winid)
    : wxScrolledWindow(parent, winid)
{
    Setup();
    UpdateStuff();
}

// init ///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void PortfolioPanel::Setup()
{
    pnlBalance = new BalancePanel(this);

    pnlPositions = new wxPanel(this);

    wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);

    wxSizerFlags flagsPnl = wxSizerFlags().Border(wxALL, 25).Expand();

    boxSizer->Add(pnlBalance, flagsPnl);
    boxSizer->Add(pnlPositions, flagsPnl);

    SetSizer(boxSizer);
    SetScrollRate(10, 10);
}

void PortfolioPanel::UpdateStuff()
{
    try
    {
        pnlBalance->UpdateStuff();

        Api::GetPositions();

        pnlPositions->DestroyChildren();

        wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);

        wxSizerFlags flagsPnl = wxSizerFlags().Border(wxUP | wxDOWN, 5).Expand();

        for (PortfolioPositionsResponse::EventPosition event : Api::GetEventPositions())
        {
            boxSizer->Add(new EventPositionPanel(pnlPositions, wxID_ANY, &event), flagsPnl);
        }

        for (PortfolioPositionsResponse::MarketPosition market : Api::GetMarketPositions())
        {
            boxSizer->Add(new MarketPositionPanel(pnlPositions, wxID_ANY, &market), flagsPnl);
        }

        pnlPositions->SetSizer(boxSizer);
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;

        wxCommandEvent* event = new wxCommandEvent(EVT_API_ERROR);
        event->SetString("Portfolio update failed!");

        event->SetEventObject(this);

        QueueEvent(event);
    }
}
