#ifndef EXCHANGESCHEDULEDIALOG_HPP
#define EXCHANGESCHEDULEDIALOG_HPP

#include <wx/wx.h>

#include "App.h" // wxfb

namespace kdeck
{
    class Api;

    class ExchangeScheduleDialog : public wxfb::ExchangeScheduleDialog
    {
    public:
        ExchangeScheduleDialog(wxWindow* parent, wxWindowID winid = wxID_ANY);

        void UpdateStuff(Api* api);
    };
}

#endif
