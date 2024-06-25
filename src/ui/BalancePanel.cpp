#include <wx/wx.h>

#include "api/Api.hpp"
#include "ui/BalancePanel.hpp"
#include "ui/StaticCurrency.hpp"
#include "ui/event.hpp"

namespace kdeck
{
    class Api;

    // constructor ////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    BalancePanel::BalancePanel(Api* api, wxWindow* parent, wxWindowID winid)
        : wxPanel(parent, winid)
        , api{api}
    {
        Setup();
    }

    // init ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    void BalancePanel::Setup()
    {
        wxStaticText* lblBalance = new wxStaticText(this, wxID_ANY, "Balance:");
        lblBalanceAmount = new StaticCurrency(this);

        wxBoxSizer* boxSizer = new wxBoxSizer(wxHORIZONTAL);

        wxSizerFlags flagsLbl = wxSizerFlags().Border(wxLEFT, 10).CenterVertical();

        boxSizer->AddStretchSpacer();
        boxSizer->Add(lblBalance, flagsLbl);
        boxSizer->Add(lblBalanceAmount, flagsLbl);

        SetSizerAndFit(boxSizer);
    }

    void BalancePanel::UpdateStuff()
    {
        if (api->IsLoggedIn())
        {
            try
            {
                lblBalanceAmount->SetAmount(api->GetBalance());
            }
            catch (std::exception &e)
            {
                std::cerr << e.what() << std::endl;

                wxCommandEvent* evt = new wxCommandEvent(EVT_API_ERROR);
                evt->SetEventObject(this);
                evt->SetString("Balance update failed!");
                QueueEvent(evt);
            }
        }
        else
        {
            lblBalanceAmount->SetAmount(0);
        }
    }
}
