#include <string>

#include <wx/wx.h>

#include "ui/PortfolioPanel.h"
#include "ui/EventPositionPanel.h"
#include "ui/MarketPositionPanel.h"
#include "api/Api.h"

// constructor ////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

PortfolioPanel::PortfolioPanel(wxWindow* parent, wxWindowID winid)
    : wxPanel(parent, winid)
{
    Setup();
    Update();
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
}

void PortfolioPanel::Update()
{
    try
    {
        pnlBalance->Update();

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

        wxLogStatus("Portfolio update succeeded!");
    }
    catch (std::logic_error &e)
    {
        wxLogError(e.what());

        wxLogStatus("Portfolio update failed!");
    }
    catch (std::runtime_error &e)
    {
        wxLogError("Unknown error.");
        wxLogDebug(e.what());

        wxLogStatus("Portfolio update failed!");
    }
}
