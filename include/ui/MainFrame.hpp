#ifndef MAINFRAME_HPP
#define MAINFRAME_HPP

#include <wx/wx.h>
#include <curlpp/cURLpp.hpp>

class PortfolioPanel;

enum
{
    ID_Login = wxID_HIGHEST + 1,
    ID_Logout = wxID_HIGHEST + 2,
};

class MainFrame : public wxFrame
{
public:
    MainFrame(wxWindow* parent = nullptr, wxWindowID winid = wxID_ANY, const wxString &title = "kdeck");

    void UpdateStuff();

private:
    // handles global cURLpp::initialize()/terminate()
    cURLpp::Cleanup cURLpp();

    wxMenuItem *mnuLogin;
    wxMenuItem *mnuLogout;

    PortfolioPanel* pnlPortfolio;

    // init
    void Setup();

    // helpers
    void DoLogin();
    void DoLogout();
    void ShowStatus(const wxString &msg);

    // event handlers
    void OnLoginOrLogout(wxCommandEvent& event);
    void OnApiError(wxCommandEvent& event);
    void OnIdleRunOnce(wxIdleEvent& event);
    void OnMenuItemSelected(wxCommandEvent& event);
    void OnClose(wxCloseEvent& event);
};

#endif