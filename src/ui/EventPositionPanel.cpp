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

    wxBoxSizer* boxSizer = new wxBoxSizer(wxHORIZONTAL);

    wxSizerFlags flagsLbl = wxSizerFlags().Border(wxALL, 10).Left();

    boxSizer->Add(lblTicker, flagsLbl);
    boxSizer->Add(lblBlank, flagsLbl);
    boxSizer->Add(lblExposure, flagsLbl);
    boxSizer->Add(lblRealizedPnL, flagsLbl);
    boxSizer->Add(lblTotalTraded, flagsLbl);
    boxSizer->Add(lblRestingOrders, flagsLbl);

    SetSizer(boxSizer);
}
