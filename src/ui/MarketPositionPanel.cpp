#include <string>

#include <memory>

#include <wx/wx.h>

#include "ui/MarketPositionPanel.hpp"
#include "ui/StaticCurrency.hpp"

namespace kdeck
{
    // constructor ////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    MarketPositionPanel::MarketPositionPanel(wxWindow* parent, wxWindowID winid, std::shared_ptr<MarketPosition> market)
        : wxPanel(parent, winid)
        , market{market}
    {
        Setup();
    }

    // init ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    void MarketPositionPanel::Setup()
    {
        wxStaticText* lblTicker = new wxStaticText(this, wxID_ANY, *market->ticker);

        wxStaticText* lblPosition;
        if (market->position > 0)
        {
            lblPosition = new wxStaticText(this, wxID_ANY, wxString::Format("Yes %d", std::abs(*market->position)));
        }
        else
        {
            lblPosition = new wxStaticText(this, wxID_ANY, wxString::Format("No %d", std::abs(*market->position)));
        }

        StaticCurrency* lblExposure = new StaticCurrency(this, wxID_ANY, *market->market_exposure);
        StaticCurrency* lblRealizedPnL = new StaticCurrency(this, wxID_ANY, *market->realized_pnl);
        StaticCurrency* lblTotalTraded = new StaticCurrency(this, wxID_ANY, *market->total_traded);
        wxStaticText* lblRestingOrders = new wxStaticText(this, wxID_ANY, std::to_string(*market->resting_orders_count));

        wxGridSizer* gridSizer = new wxGridSizer(6, wxSize{10, 0});

        wxSizerFlags flagsLblLeft = wxSizerFlags().CenterVertical().Left();
        wxSizerFlags flagsLblRight = wxSizerFlags().CenterVertical().Right();

        gridSizer->Add(lblTicker, flagsLblLeft);
        gridSizer->Add(lblPosition, flagsLblRight);
        gridSizer->Add(lblExposure, flagsLblRight);
        gridSizer->Add(lblRealizedPnL, flagsLblRight);
        gridSizer->Add(lblTotalTraded, flagsLblRight);
        gridSizer->Add(lblRestingOrders, flagsLblRight);

        SetSizerAndFit(gridSizer);
    }
}
