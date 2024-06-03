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

    wxBoxSizer* boxSizer = new wxBoxSizer(wxHORIZONTAL);

    wxSizerFlags flagsLbl = wxSizerFlags().Border(wxALL, 10).Left();

    boxSizer->Add(lblTicker, flagsLbl);
    boxSizer->Add(lblPosition, flagsLbl);
    boxSizer->Add(lblExposure, flagsLbl);
    boxSizer->Add(lblRealizedPnL, flagsLbl);
    boxSizer->Add(lblTotalTraded, flagsLbl);
    boxSizer->Add(lblRestingOrders, flagsLbl);

    SetSizer(boxSizer);
}
