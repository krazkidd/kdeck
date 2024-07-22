#include <wx/wx.h>

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
        : wxScrolledWindow(parent, winid)
    {
        Setup();
    }

    // init ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    void PortfolioPanel::Setup()
    {
        pnlBalance = new BalancePanel(this);

        pnlPositions = new wxPanel(this);

        wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);

        wxSizerFlags flags = wxSizerFlags().Border(wxALL, 10).Expand();

        boxSizer->Add(pnlBalance, flags);
        boxSizer->Add(pnlPositions, flags);

        SetSizerAndFit(boxSizer);
        SetScrollRate(10, 10);
    }

    void PortfolioPanel::UpdateStuff(const Config* config, Api* api)
    {
        pnlBalance->UpdateStuff(api);

        pnlPositions->DestroyChildren();

        if (api->IsLoggedIn())
        {
            try
            {
                api->GetPositions();

                wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);

                wxSizerFlags flags = wxSizerFlags().Border(wxUP | wxDOWN, 10).Expand();

                for (auto event : api->GetEventPositions())
                {
                    if (0 == *event->event_exposure && !config->GetShowClosedPositions())
                    {
                        continue;
                    }

                    boxSizer->Add(new EventPositionPanel(pnlPositions, wxID_ANY, event), flags);

                    for (auto market : api->GetMarketPositions(*event->event_ticker))
                    {
                        if (0 == *market->market_exposure && !config->GetShowClosedPositions())
                        {
                            continue;
                        }

                        boxSizer->Add(new MarketPositionPanel(pnlPositions, wxID_ANY, market), flags);
                    }
                }

                pnlPositions->SetSizerAndFit(boxSizer);
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
