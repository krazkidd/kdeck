#include <wx/wx.h>

#include "PortfolioPanel.h" // wxfb

#include "api/Api.hpp"
#include "config/Config.hpp"
#include "ui/BalancePanel.hpp"
#include "ui/PortfolioPanel.hpp"
#include "ui/EventPositionPanel.hpp"
#include "ui/MarketPositionPanel.hpp"
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
        pnlBalance->UpdateStuff(api);

        pnlPositions->DestroyChildren();

        if (api->IsLoggedIn())
        {
            try
            {
                api->GetPositions();

                wxSizerFlags flags = wxSizerFlags().Border(wxUP | wxDOWN, 10).Expand();
                for (auto event : api->GetEventPositions())
                {
                    if (0 == *event->event_exposure && !config->GetShowClosedPositions())
                    {
                        continue;
                    }

                    vszrPositions->Add(new EventPositionPanel(pnlPositions, wxID_ANY, event), flags);

                    for (auto market : api->GetMarketPositions(*event->event_ticker))
                    {
                        if (0 == *market->market_exposure && !config->GetShowClosedPositions())
                        {
                            continue;
                        }

                        vszrPositions->Add(new MarketPositionPanel(pnlPositions, wxID_ANY, market), flags);
                    }
                }
                pnlPositions->Layout();
            }
            catch (const std::exception &e)
            {
                wxCommandEvent* evt = new wxCommandEvent(EVT_API_ERROR);
                evt->SetEventObject(this);
                evt->SetString("Portfolio update failed!");
                QueueEvent(evt);
            }
        }
    }
}
