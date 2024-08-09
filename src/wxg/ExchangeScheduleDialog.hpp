// -*- C++ -*-
//
// generated by wxGlade 1.1.0b1 on Fri Aug  9 15:39:27 2024
//
// Example for compiling a single file project under Linux using g++:
//  g++ MyApp.cpp $(wx-config --libs) $(wx-config --cxxflags) -o MyApp
//
// Example for compiling a multi file project under Linux using g++:
//  g++ main.cpp $(wx-config --libs) $(wx-config --cxxflags) -o MyApp Dialog1.cpp Frame1.cpp
//

#ifndef EXCHANGESCHEDULEDIALOG_HPP
#define EXCHANGESCHEDULEDIALOG_HPP

#include <wx/wx.h>
#include <wx/image.h>
#include <wx/intl.h>

#ifndef APP_CATALOG
#define APP_CATALOG "App"  // replace with the appropriate catalog name
#endif


// begin wxGlade: ::dependencies
// end wxGlade

// begin wxGlade: ::extracode
// end wxGlade


class ExchangeScheduleDialog: public wxDialog {
public:
    // begin wxGlade: ExchangeScheduleDialog::ids
    // end wxGlade

    ExchangeScheduleDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=wxDEFAULT_DIALOG_STYLE);

private:

protected:
    // begin wxGlade: ExchangeScheduleDialog::attributes
    wxTextCtrl* txtSundaySchedule;
    wxTextCtrl* txtMondaySchedule;
    wxTextCtrl* txtTuesdaySchedule;
    wxTextCtrl* txtWednesdaySchedule;
    wxTextCtrl* txtThursdaySchedule;
    wxTextCtrl* txtFridaySchedule;
    wxTextCtrl* txtSaturdaySchedule;
    wxPanel* panel_1;
    wxButton* button_OK;
    // end wxGlade
}; // wxGlade: end class


#endif // EXCHANGESCHEDULEDIALOG_HPP
