#ifndef MAINFRAME_HPP
#define MAINFRAME_HPP

#include <wx/wx.h>
#include <curlpp/cURLpp.hpp>

#include "config.hpp"
#include "api/Api.hpp"

class PortfolioPanel;

enum
{
    ID_Login = wxID_HIGHEST + 1,
    ID_Logout = wxID_HIGHEST + 2,
    ID_Exchange_Announcements = wxID_HIGHEST + 3,
    ID_Exchange_Schedule = wxID_HIGHEST + 4,
    ID_Exchange_Status = wxID_HIGHEST + 5
};

class MainFrame : public wxFrame
{
public:
    MainFrame(wxWindow* parent = nullptr, wxWindowID winid = wxID_ANY, const wxString &title = std::string{kProjectName});

    void UpdateStuff();

private:
    // handles global cURLpp::initialize()/terminate()
    cURLpp::Cleanup cURLpp();

    Api api;

    wxMenuItem *mnuLogin;
    wxMenuItem *mnuLogout;

    PortfolioPanel* pnlPortfolio;

    // init
    void Setup();

    // helpers
    void DoLogin();
    void DoLogout();
    void DoShowExchangeAnnouncements();
    void DoShowExchangeSchedule();
    void DoShowExchangeStatus();

    void ShowStatus(const wxString &msg);

    // event handlers
    void OnLoginOrLogout(wxCommandEvent& event);
    void OnApiError(wxCommandEvent& event);
    void OnIdleRunOnce(wxIdleEvent& event);
    void OnMenuItemSelected(wxCommandEvent& event);
    void OnClose(wxCloseEvent& event);
};

#endif