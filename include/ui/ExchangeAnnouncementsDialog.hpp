#ifndef EXCHANGEANNOUNCEMENTDIALOG_HPP
#define EXCHANGEANNOUNCEMENTDIALOG_HPP

#include <wx/wx.h>

namespace kdeck
{
    class Api;

    class ExchangeAnnouncementsDialog : public wxDialog
    {
    public:
        ExchangeAnnouncementsDialog(Api* api, wxWindow* parent, wxWindowID winid = wxID_ANY, const wxString &title = "Exchange Announcements");

        void UpdateStuff();

        virtual bool Show(bool show = true) override;

    private:
        Api* api;

        wxBoxSizer* boxSizer;

        // init
        void Setup();
    };
}

#endif
