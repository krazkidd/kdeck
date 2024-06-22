#ifndef EXCHANGESTATUSDIALOG_HPP
#define EXCHANGESTATUSDIALOG_HPP

#include <wx/wx.h>

class ExchangeStatusDialog : public wxDialog
{
public:
    ExchangeStatusDialog(wxWindow* parent, wxWindowID winid = wxID_ANY, const wxString &title = "Exchange Status");

    void UpdateStuff();

    virtual bool Show(bool show = true) override;

private:
    wxStaticText* lblExchangeStatus;
    wxStaticText* lblTradingStatus;

    // init
    void Setup();
};

#endif