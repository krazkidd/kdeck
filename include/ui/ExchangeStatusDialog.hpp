#ifndef EXCHANGESTATUSDIALOG_HPP
#define EXCHANGESTATUSDIALOG_HPP

#include <wx/wx.h>

class ExchangeStatusDialog : public wxDialog
{
public:
    ExchangeStatusDialog(wxWindow* parent, wxWindowID winid = wxID_ANY, const wxString &title = "Exchange Status");

private:
    // init
    void Setup();
};

#endif