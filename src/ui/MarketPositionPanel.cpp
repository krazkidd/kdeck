#include <string>

#include <wx/wx.h>

#include "ui/MarketPositionPanel.h"

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
    wxStaticText* lblExposure = new wxStaticText(this, wxID_ANY, std::to_string(market->market_exposure));
    wxStaticText* lblRealizedPnL = new wxStaticText(this, wxID_ANY, std::to_string(market->realized_pnl));
    wxStaticText* lblTotalTraded = new wxStaticText(this, wxID_ANY, std::to_string(market->total_traded));
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
