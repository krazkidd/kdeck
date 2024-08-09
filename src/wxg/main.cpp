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

// This is an automatically generated file.
// Manual changes will be overwritten without warning!

#include <wx/wx.h>
#include <wx/image.h>
#include <wx/intl.h>

#ifndef APP_CATALOG
#define APP_CATALOG "App"  // replace with the appropriate catalog name
#endif

#include "MainFrame.hpp"


class App: public wxApp {
public:
    bool OnInit();
protected:
    wxLocale m_locale;  // locale we'll be using
};

IMPLEMENT_APP(App)

bool App::OnInit()
{
    m_locale.Init();
#ifdef APP_LOCALE_DIR
    m_locale.AddCatalogLookupPathPrefix(wxT(APP_LOCALE_DIR));
#endif
    m_locale.AddCatalog(wxT(APP_CATALOG));

    wxInitAllImageHandlers();
    MainFrame* frame = new MainFrame(NULL, wxID_ANY, wxEmptyString);
    SetTopWindow(frame);
    frame->Show();
    return true;
}
