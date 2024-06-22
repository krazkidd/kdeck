#ifndef EXCHANGEANNOUNCEMENTDIALOG_HPP
#define EXCHANGEANNOUNCEMENTDIALOG_HPP

#include <wx/wx.h>

class ExchangeAnnouncementsDialog : public wxDialog
{
public:
    ExchangeAnnouncementsDialog(wxWindow* parent, wxWindowID winid = wxID_ANY, const wxString &title = "Exchange Announcements");

    void UpdateStuff();

    virtual bool Show(bool show = true) override;

private:
    wxBoxSizer* boxSizer;

    // init
    void Setup();
};

#endif