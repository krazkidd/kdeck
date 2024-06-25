#ifndef EXCHANGESTATUSDIALOG_HPP
#define EXCHANGESTATUSDIALOG_HPP

#include <wx/wx.h>

namespace kdeck
{
    class Api;

    class ExchangeStatusDialog : public wxDialog
    {
    public:
        ExchangeStatusDialog(wxWindow* parent, wxWindowID winid = wxID_ANY, const wxString &title = "Exchange Status");

        void UpdateStuff(Api* api);

    private:
        wxStaticText* lblExchangeStatus;
        wxStaticText* lblTradingStatus;

        // init
        void Setup();
    };
}

#endif
