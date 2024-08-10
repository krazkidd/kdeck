// -*- C++ -*-
//
// generated by wxGlade 1.1.0b1 on Fri Aug  9 23:34:07 2024
//
// Example for compiling a single file project under Linux using g++:
//  g++ MyApp.cpp $(wx-config --libs) $(wx-config --cxxflags) -o MyApp
//
// Example for compiling a multi file project under Linux using g++:
//  g++ main.cpp $(wx-config --libs) $(wx-config --cxxflags) -o MyApp Dialog1.cpp Frame1.cpp
//

#ifndef BASELOGOUTDIALOG_HPP
#define BASELOGOUTDIALOG_HPP

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


class BaseLogoutDialog: public wxDialog {
public:
    // begin wxGlade: BaseLogoutDialog::ids
    // end wxGlade

    BaseLogoutDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize, long style=wxDEFAULT_DIALOG_STYLE);

private:

protected:
    // begin wxGlade: BaseLogoutDialog::attributes
    wxButton* button_OK;
    wxButton* button_CANCEL;
    // end wxGlade
}; // wxGlade: end class


#endif // BASELOGOUTDIALOG_HPP