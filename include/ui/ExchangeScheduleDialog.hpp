#ifndef EXCHANGESCHEDULEDIALOG_HPP
#define EXCHANGESCHEDULEDIALOG_HPP

#include <wx/wx.h>

namespace kdeck
{
    class Api;

    class ExchangeScheduleDialog : public wxDialog
    {
    public:
        ExchangeScheduleDialog(wxWindow* parent, wxWindowID winid = wxID_ANY, const wxString &title = "Exchange Schedule");

        void UpdateStuff(Api* api);

    private:
        wxStaticText* lblSundaySchedule;
        wxStaticText* lblMondaySchedule;
        wxStaticText* lblTuesdaySchedule;
        wxStaticText* lblWednesdaySchedule;
        wxStaticText* lblThursdaySchedule;
        wxStaticText* lblFridaySchedule;
        wxStaticText* lblSaturdaySchedule;

        wxBoxSizer* boxSizer;

        // init
        void Setup();
    };
}

#endif
