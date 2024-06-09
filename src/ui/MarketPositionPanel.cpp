#include <string>

#include <wx/wx.h>

#include "ui/MarketPositionPanel.h"
#include "ui/StaticCurrency.h"

// constructor ////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

MarketPositionPanel::MarketPositionPanel(wxWindow* parent, wxWindowID winid, PortfolioPositionsResponse::MarketPosition* market)
    : wxPanel(parent, winid)
    , market{market}
{
    Setup();
}

// init ///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void MarketPositionPanel::Setup()
{
    wxStaticText* lblTicker = new wxStaticText(this, wxID_ANY, market->ticker);
    wxStaticText* lblPosition = new wxStaticText(this, wxID_ANY, std::to_string(market->position));
    StaticCurrency* lblExposure = new StaticCurrency(this, wxID_ANY, market->market_exposure);
    StaticCurrency* lblRealizedPnL = new StaticCurrency(this, wxID_ANY, market->realized_pnl);
    StaticCurrency* lblTotalTraded = new StaticCurrency(this, wxID_ANY, market->total_traded);
    wxStaticText* lblRestingOrders = new wxStaticText(this, wxID_ANY, std::to_string(market->resting_orders_count));

    wxGridSizer* gridSizer = new wxGridSizer(6, wxSize{10, 0});

    wxSizerFlags flagsLblLeft = wxSizerFlags().CenterVertical().Left();
    wxSizerFlags flagsLblRight = wxSizerFlags().CenterVertical().Right();

    gridSizer->Add(lblTicker, flagsLblLeft);
    gridSizer->Add(lblPosition, flagsLblRight);
    gridSizer->Add(lblExposure, flagsLblRight);
    gridSizer->Add(lblRealizedPnL, flagsLblRight);
    gridSizer->Add(lblTotalTraded, flagsLblRight);
    gridSizer->Add(lblRestingOrders, flagsLblRight);

    SetSizer(gridSizer);
}
