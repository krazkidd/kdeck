#include <string>

#include <wx/wx.h>

#include "ui/MarketPositionPanel.h"
#include "ui/MainFrame.h"
#include "api/Api.h"

// constructor ////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

MarketPositionPanel::MarketPositionPanel(wxWindow* parent, PortfolioPositionsResponse::MarketPosition* position)
    : wxPanel(parent, wxID_ANY)
    , position{position}
{
    Setup();
}

// init ///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void MarketPositionPanel::Setup()
{
    wxStaticText* lblTicker = new wxStaticText(this, wxID_ANY, position->ticker);
    wxStaticText* lblPosition = new wxStaticText(this, wxID_ANY, std::to_string(position->position));
    wxStaticText* lblMarketExposure = new wxStaticText(this, wxID_ANY, std::to_string(position->market_exposure));
    wxStaticText* lblRealizedPnL = new wxStaticText(this, wxID_ANY, std::to_string(position->realized_pnl));
    wxStaticText* lblTotalTraded = new wxStaticText(this, wxID_ANY, std::to_string(position->total_traded));
    wxStaticText* lblRestingOrders = new wxStaticText(this, wxID_ANY, std::to_string(position->resting_orders_count));

    wxBoxSizer* boxSizer = new wxBoxSizer(wxHORIZONTAL);

    wxSizerFlags flagsLbl = wxSizerFlags().Border(wxALL, 10).Left();
    //wxSizerFlags flagsInput = wxSizerFlags().Border(wxALL, 25).Expand();

    boxSizer->Add(lblTicker, flagsLbl);
    boxSizer->Add(lblPosition, flagsLbl);
    boxSizer->Add(lblMarketExposure, flagsLbl);
    boxSizer->Add(lblRealizedPnL, flagsLbl);
    boxSizer->Add(lblTotalTraded, flagsLbl);
    boxSizer->Add(lblRestingOrders, flagsLbl);

    //TODO this doesn't seem to be working (there is overlapping text)
    SetSizer(boxSizer);
    boxSizer->SetSizeHints(this);
}
