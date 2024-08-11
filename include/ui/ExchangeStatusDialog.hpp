#ifndef EXCHANGESTATUSDIALOG_HPP
#define EXCHANGESTATUSDIALOG_HPP

#include <wx/wx.h>

#include "App.h" // wxfb

namespace kdeck
{
    class Api;

    class ExchangeStatusDialog : public wxfb::ExchangeStatusDialog
    {
    public:
        ExchangeStatusDialog(wxWindow* parent, wxWindowID winid = wxID_ANY, const wxString &title = "Exchange Status");

        void UpdateStuff(Api* api);
    };
}

#endif
