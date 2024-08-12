#ifndef EXCHANGEANNOUNCEMENTDIALOG_HPP
#define EXCHANGEANNOUNCEMENTDIALOG_HPP

#include <wx/wx.h>

#include "App.h" // wxfb

namespace kdeck
{
    class Api;

    class ExchangeAnnouncementsDialog : public wxfb::ExchangeAnnouncementsDialog
    {
    public:
        ExchangeAnnouncementsDialog(wxWindow* parent, wxWindowID winid = wxID_ANY)
            : wxfb::ExchangeAnnouncementsDialog(parent, winid) {};

        void UpdateStuff(Api* api);
    };
}

#endif
