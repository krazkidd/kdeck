#ifndef EXCHANGESCHEDULEDIALOG_HPP
#define EXCHANGESCHEDULEDIALOG_HPP

#include <wx/wx.h>

class ExchangeScheduleDialog : public wxDialog
{
public:
    ExchangeScheduleDialog(wxWindow* parent, wxWindowID winid = wxID_ANY, const wxString &title = "Exchange Schedule");

    void UpdateStuff();

    virtual bool Show(bool show = true) override;

private:
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

#endif