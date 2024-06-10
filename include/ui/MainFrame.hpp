#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>
#include <curlpp/cURLpp.hpp>

enum
{
    //ID_Login = wxID_HIGHEST + 1,
    ID_Logout = wxID_HIGHEST + 2,
};

class MainFrame : public wxFrame
{
public:
    MainFrame(wxWindow* parent = nullptr, wxWindowID winid = wxID_ANY, const wxString &title = "kdeck");

private:
    // handles global cURLpp::initialize()/terminate()
    cURLpp::Cleanup cURLpp();

    wxMenuItem *logoutMenuItem;

    // init
    void Setup();
    void UpdateStuff();

    // event handlers
    void OnLoginOrLogout(wxCommandEvent& event);
    void OnApiError(wxCommandEvent& event);
    void OnLogoutMenuItemSelected(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnClose(wxCloseEvent& event);
};

#endif