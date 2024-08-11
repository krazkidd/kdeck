#include <wx/wx.h>

#include "PortfolioPanel.h" // wxfb

#include "api/Api.hpp"
#include "config/Config.hpp"
#include "ui/PortfolioPanel.hpp"
#include "ui/event.hpp"

namespace kdeck
{
    // constructor ////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    PortfolioPanel::PortfolioPanel(wxWindow* parent, wxWindowID winid)
        : wxfb::PortfolioPanel(parent, winid)
    {

    }

    // init ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    void PortfolioPanel::UpdateStuff(const Config* config, Api* api)
    {
        pnlPositions->DestroyChildren();

        if (api->IsLoggedIn())
        {
            try
            {
                lblBalanceAmount->SetAmount(api->GetBalance());

                api->GetPositions();

                wxSizerFlags flagsLblLeft = wxSizerFlags().CenterVertical().Left();
                wxSizerFlags flagsLblRight = wxSizerFlags().CenterVertical().Right();
                for (auto event : api->GetEventPositions())
                {
                    if (0 == *event->event_exposure && !config->GetShowClosedPositions())
                    {
                        continue;
                    }

                    wxStaticText* lblTicker = new wxStaticText(pnlPositions, wxID_ANY, *event->event_ticker);
                    wxStaticText* lblBlank = new wxStaticText(pnlPositions, wxID_ANY, "");
                    StaticCurrency* lblExposure = new StaticCurrency(pnlPositions, wxID_ANY, *event->event_exposure);
                    StaticCurrency* lblRealizedPnL = new StaticCurrency(pnlPositions, wxID_ANY, *event->realized_pnl);
                    StaticCurrency* lblTotalTraded = new StaticCurrency(pnlPositions, wxID_ANY, *event->total_cost);
                    wxStaticText* lblRestingOrders = new wxStaticText(pnlPositions, wxID_ANY, std::to_string(*event->resting_order_count));

                    fgszrPositions->Add(lblTicker, flagsLblLeft);
                    fgszrPositions->Add(lblBlank, flagsLblRight);
                    fgszrPositions->Add(lblExposure, flagsLblRight);
                    fgszrPositions->Add(lblRealizedPnL, flagsLblRight);
                    fgszrPositions->Add(lblTotalTraded, flagsLblRight);
                    fgszrPositions->Add(lblRestingOrders, flagsLblRight);

                    for (auto market : api->GetMarketPositions(*event->event_ticker))
                    {
                        if (0 == *market->market_exposure && !config->GetShowClosedPositions())
                        {
                            continue;
                        }

                        wxStaticText* lblTicker = new wxStaticText(pnlPositions, wxID_ANY, *market->ticker);

                        wxStaticText* lblPosition;
                        if (market->position > 0)
                        {
                            lblPosition = new wxStaticText(pnlPositions, wxID_ANY, wxString::Format("Yes %d", std::abs(*market->position)));
                        }
                        else
                        {
                            lblPosition = new wxStaticText(pnlPositions, wxID_ANY, wxString::Format("No %d", std::abs(*market->position)));
                        }

                        StaticCurrency* lblExposure = new StaticCurrency(pnlPositions, wxID_ANY, *market->market_exposure);
                        StaticCurrency* lblRealizedPnL = new StaticCurrency(pnlPositions, wxID_ANY, *market->realized_pnl);
                        StaticCurrency* lblTotalTraded = new StaticCurrency(pnlPositions, wxID_ANY, *market->total_traded);
                        wxStaticText* lblRestingOrders = new wxStaticText(pnlPositions, wxID_ANY, std::to_string(*market->resting_orders_count));

                        fgszrPositions->Add(lblTicker, flagsLblLeft);
                        fgszrPositions->Add(lblPosition, flagsLblRight);
                        fgszrPositions->Add(lblExposure, flagsLblRight);
                        fgszrPositions->Add(lblRealizedPnL, flagsLblRight);
                        fgszrPositions->Add(lblTotalTraded, flagsLblRight);
                        fgszrPositions->Add(lblRestingOrders, flagsLblRight);
                    }
                }
            }
            catch (const std::exception &e)
            {
                wxCommandEvent* evt = new wxCommandEvent(EVT_API_ERROR);
                evt->SetEventObject(this);
                evt->SetString("Portfolio update failed!");
                QueueEvent(evt);
            }
        }
        else
        {
            lblBalanceAmount->SetAmount(0);
        }

        Layout();
    }
}
