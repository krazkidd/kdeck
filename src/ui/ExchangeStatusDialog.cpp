#include <wx/wx.h>

#include "api/Api.hpp"
#include "ui/ExchangeStatusDialog.hpp"
#include "ui/event.hpp"

namespace kdeck
{
    class ExchangeStatusResponse;

    // constructor ////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    ExchangeStatusDialog::ExchangeStatusDialog(wxWindow* parent, wxWindowID winid, const wxString &title)
        : wxfb::ExchangeStatusDialog(parent, winid, title)
    {

    }

    void ExchangeStatusDialog::UpdateStuff(Api* api)
    {
        try
        {
            std::shared_ptr<ExchangeStatusResponse> status = api->GetExchangeStatus();

            if (status->exchange_active)
            {
                lblExchangeStatus->SetLabel(L"🟢 Active");
            }
            else
            {
                lblExchangeStatus->SetLabel(L"🔴 Not active");
            }

            if (status->trading_active)
            {
                lblTradingStatus->SetLabel(L"🟢 Active");
            }
            else
            {
                lblTradingStatus->SetLabel(L"🔴 Not active");
            }
        }
        catch (const std::exception &e)
        {
            wxCommandEvent* evt = new wxCommandEvent(EVT_API_ERROR);
            evt->SetEventObject(this);
            evt->SetString("Exchange status failed!");
            QueueEvent(evt);
        }
    }
}
