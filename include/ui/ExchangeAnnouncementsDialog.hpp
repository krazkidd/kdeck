#ifndef EXCHANGEANNOUNCEMENTDIALOG_HPP
#define EXCHANGEANNOUNCEMENTDIALOG_HPP

#include <wx/wx.h>

class ExchangeAnnouncementsDialog : public wxDialog
{
public:
    ExchangeAnnouncementsDialog(wxWindow* parent, wxWindowID winid = wxID_ANY, const wxString &title = "Exchange Announcements");

private:
    // init
    void Setup();
};

#endif