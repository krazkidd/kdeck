#ifndef EXCHANGESCHEDULEDIALOG_HPP
#define EXCHANGESCHEDULEDIALOG_HPP

#include <wx/wx.h>

class ExchangeScheduleDialog : public wxDialog
{
public:
    ExchangeScheduleDialog(wxWindow* parent, wxWindowID winid = wxID_ANY, const wxString &title = "Exchange Schedule");

private:
    // init
    void Setup();
};

#endif