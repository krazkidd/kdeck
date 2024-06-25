#include <wx/wx.h>

#include "api/Api.hpp"
#include "ui/BalancePanel.hpp"
#include "ui/PortfolioPanel.hpp"
#include "ui/EventPositionPanel.hpp"
#include "ui/MarketPositionPanel.hpp"
#include "ui/event.hpp"

namespace kdeck
{
    class Api;

    // constructor ////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    PortfolioPanel::PortfolioPanel(Api* api, wxWindow* parent, wxWindowID winid)
        : wxScrolledWindow(parent, winid)
        , api{api}
    {
        Setup();
    }

    // init ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    void PortfolioPanel::Setup()
    {
        pnlBalance = new BalancePanel(api, this);

        pnlPositions = new wxPanel(this);

        wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);

        wxSizerFlags flagsPnl = wxSizerFlags().Border(wxALL, 25).Expand();

        boxSizer->Add(pnlBalance, flagsPnl);
        boxSizer->Add(pnlPositions, flagsPnl);

        SetSizerAndFit(boxSizer);
        SetScrollRate(10, 10);
    }

    void PortfolioPanel::UpdateStuff()
    {
        pnlBalance->UpdateStuff();

        pnlPositions->DestroyChildren();

        if (api->IsLoggedIn())
        {
            try
            {
                api->GetPositions();

                wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);

                wxSizerFlags flagsPnl = wxSizerFlags().Border(wxUP | wxDOWN, 5).Expand();

                for (PortfolioPositionsResponse::EventPosition event : api->GetEventPositions())
                {
                    boxSizer->Add(new EventPositionPanel(pnlPositions, wxID_ANY, &event), flagsPnl);

                    for (PortfolioPositionsResponse::MarketPosition market : api->GetMarketPositions(event.event_ticker))
                    {
                        boxSizer->Add(new MarketPositionPanel(pnlPositions, wxID_ANY, &market), flagsPnl);
                    }
                }

                pnlPositions->SetSizerAndFit(boxSizer);
            }
            catch (std::exception &e)
            {
                std::cerr << e.what() << std::endl;

                wxCommandEvent* evt = new wxCommandEvent(EVT_API_ERROR);
                evt->SetEventObject(this);
                evt->SetString("Portfolio update failed!");
                QueueEvent(evt);
            }
        }
    }
}
