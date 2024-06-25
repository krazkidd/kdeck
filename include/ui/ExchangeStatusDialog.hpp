#ifndef EXCHANGESTATUSDIALOG_HPP
#define EXCHANGESTATUSDIALOG_HPP

#include <wx/wx.h>

namespace kdeck
{
    class Api;

    class ExchangeStatusDialog : public wxDialog
    {
    public:
        ExchangeStatusDialog(Api* api, wxWindow* parent, wxWindowID winid = wxID_ANY, const wxString &title = "Exchange Status");

        void UpdateStuff();

        virtual bool Show(bool show = true) override;

    private:
        Api* api;

        wxStaticText* lblExchangeStatus;
        wxStaticText* lblTradingStatus;

        // init
        void Setup();
    };
}

#endif
