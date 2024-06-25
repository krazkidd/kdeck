#ifndef EXCHANGESCHEDULEDIALOG_HPP
#define EXCHANGESCHEDULEDIALOG_HPP

#include <wx/wx.h>

namespace kdeck
{
    class Api;

    class ExchangeScheduleDialog : public wxDialog
    {
    public:
        ExchangeScheduleDialog(Api* api, wxWindow* parent, wxWindowID winid = wxID_ANY, const wxString &title = "Exchange Schedule");

        void UpdateStuff();

        virtual bool Show(bool show = true) override;

    private:
        Api* api;

        wxStaticText* lblSundaySchedule;
        wxStaticText* lblMondaySchedule;
        wxStaticText* lblTuesdaySchedule;
        wxStaticText* lblWednesdaySchedule;
        wxStaticText* lblThursdaySchedule;
        wxStaticText* lblFridaySchedule;
        wxStaticText* lblSaturdaySchedule;

        // init
        void Setup();
    };
}

#endif
