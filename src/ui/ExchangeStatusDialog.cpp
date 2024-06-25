#include <wx/wx.h>

#include "api/Api.hpp"
#include "api/types.hpp"
#include "ui/ExchangeStatusDialog.hpp"
#include "ui/event.hpp"

namespace kdeck
{
    // constructor ////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    ExchangeStatusDialog::ExchangeStatusDialog(wxWindow* parent, wxWindowID winid, const wxString &title)
        : wxDialog(parent, winid, title)
    {
        Setup();
    }

    // init ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    void ExchangeStatusDialog::Setup()
    {
        wxStaticText* lblExchange = new wxStaticText(this, wxID_ANY, "Exchange:");
        lblExchangeStatus = new wxStaticText(this, wxID_ANY, "");

        wxStaticText* lblTrading = new wxStaticText(this, wxID_ANY, "Trading:");
        lblTradingStatus = new wxStaticText(this, wxID_ANY, "");

        ///////////////////////////////////////////////////////////////////////////

        wxGridSizer* gridSizer = new wxGridSizer(2, 2, wxSize{10, 10});

        wxSizerFlags flagsLblLeft = wxSizerFlags().CenterVertical().Left();
        wxSizerFlags flagsLblRight = wxSizerFlags().CenterVertical().Right();

        gridSizer->Add(lblExchange, flagsLblRight);
        gridSizer->Add(lblExchangeStatus, flagsLblLeft);

        gridSizer->Add(lblTrading, flagsLblRight);
        gridSizer->Add(lblTradingStatus, flagsLblLeft);

        ///////////////////////////////////////////////////////////////////////////

        wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);

        boxSizer->Add(gridSizer, wxSizerFlags().Border(wxALL, 10).Expand());

        wxSizer* szrButton = CreateButtonSizer(wxOK);
        if (szrButton)
        {
            boxSizer->Add(szrButton, wxSizerFlags().Center());
        }

        SetSizerAndFit(boxSizer);
    }

    void ExchangeStatusDialog::UpdateStuff(Api* api)
    {
        try
        {
            ExchangeStatusResponse status = api->GetExchangeStatus();

            if (status.exchange_active)
            {
                lblExchangeStatus->SetLabel(L"🟢 Active");
            }
            else
            {
                lblExchangeStatus->SetLabel(L"🔴 Not active");
            }

            if (status.trading_active)
            {
                lblTradingStatus->SetLabel(L"🟢 Active");
            }
            else
            {
                lblTradingStatus->SetLabel(L"🔴 Not active");
            }
        }
        catch (std::exception &e)
        {
            std::cerr << e.what() << std::endl;

            wxCommandEvent* evt = new wxCommandEvent(EVT_API_ERROR);
            evt->SetEventObject(this);
            evt->SetString("Exchange status failed!");
            QueueEvent(evt);
        }
    }
}
