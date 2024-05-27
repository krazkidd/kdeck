#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>
#include <curlpp/cURLpp.hpp>

enum
{
    //TODO i think i heard this can't be 0 or 1?
    ID_Login = 1,
    ID_Logout = 2,
};

class MainFrame : public wxFrame
{
public:
    MainFrame();

private:
    // handles global cURLpp::initialize()/terminate()
    cURLpp::Cleanup cURLpp();

    wxMenuItem *logoutMenuItem;

    // init
    void Setup();
    void Update();

    // event handlers
    void OnLoginButtonClicked(wxCommandEvent& event);
    void OnLogoutMenuItemSelected(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
};

#endif