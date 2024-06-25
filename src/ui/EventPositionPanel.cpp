#include <string>

#include <wx/wx.h>

#include "ui/EventPositionPanel.hpp"
#include "ui/StaticCurrency.hpp"

namespace kdeck
{
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
        StaticCurrency* lblExposure = new StaticCurrency(this, wxID_ANY, event->event_exposure);
        StaticCurrency* lblRealizedPnL = new StaticCurrency(this, wxID_ANY, event->realized_pnl);
        StaticCurrency* lblTotalTraded = new StaticCurrency(this, wxID_ANY, event->total_cost);
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

        SetSizerAndFit(gridSizer);
    }
}
