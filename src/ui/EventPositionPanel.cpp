#include <string>

#include <wx/wx.h>

#include "ui/EventPositionPanel.h"

// constructor ////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

EventPositionPanel::EventPositionPanel(wxWindow* parent, wxWindowID winid, PortfolioPositionsResponse::EventPosition* event)
    : wxPanel(parent, winid)
    , event{event}
{
    Setup();
}

// init ///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void EventPositionPanel::Setup()
{
    wxStaticText* lblTicker = new wxStaticText(this, wxID_ANY, event->event_ticker);
    wxStaticText* lblBlank = new wxStaticText(this, wxID_ANY, "");
    wxStaticText* lblExposure = new wxStaticText(this, wxID_ANY, std::to_string(event->event_exposure));
    wxStaticText* lblRealizedPnL = new wxStaticText(this, wxID_ANY, std::to_string(event->realized_pnl));
    wxStaticText* lblTotalTraded = new wxStaticText(this, wxID_ANY, std::to_string(event->total_cost));
    wxStaticText* lblRestingOrders = new wxStaticText(this, wxID_ANY, std::to_string(event->resting_order_count));

    wxGridSizer* gridSizer = new wxGridSizer(6, wxSize{10, 0});

    wxSizerFlags flagsLblLeft = wxSizerFlags().CenterVertical().Left();
    wxSizerFlags flagsLblRight = wxSizerFlags().CenterVertical().Right();

    gridSizer->Add(lblTicker, flagsLblLeft);
    gridSizer->Add(lblBlank, flagsLblRight);
    gridSizer->Add(lblExposure, flagsLblRight);
    gridSizer->Add(lblRealizedPnL, flagsLblRight);
    gridSizer->Add(lblTotalTraded, flagsLblRight);
    gridSizer->Add(lblRestingOrders, flagsLblRight);

    SetSizer(gridSizer);
}
