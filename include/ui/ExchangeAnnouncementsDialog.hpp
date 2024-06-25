#ifndef EXCHANGEANNOUNCEMENTDIALOG_HPP
#define EXCHANGEANNOUNCEMENTDIALOG_HPP

#include <wx/wx.h>

namespace kdeck
{
    class Api;

    class ExchangeAnnouncementsDialog : public wxDialog
    {
    public:
        ExchangeAnnouncementsDialog(wxWindow* parent, wxWindowID winid = wxID_ANY, const wxString &title = "Exchange Announcements");

        void UpdateStuff(Api* api);

    private:
        wxBoxSizer* boxSizer;

        // init
        void Setup();
    };
}

#endif
