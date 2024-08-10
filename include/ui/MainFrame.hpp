#ifndef MAINFRAME_HPP
#define MAINFRAME_HPP

#include <wx/wx.h>

#include "app_config.hpp"
#include "api/Api.hpp"
#include "config/Config.hpp"
#include "ui/enum.hpp"

namespace kdeck
{
    class PortfolioPanel;

    class MainFrame : public wxFrame
    {
    public:
        MainFrame(wxWindow* parent = nullptr, wxWindowID winid = wxID_ANY, const wxString &title = std::string{kProjectName});

        void UpdateStuff();

    private:
        // config must be ordered before api (see constructor in MainFrame.cpp)
        Config config;
        Api api;

        wxMenuItem *mnuLogin;
        wxMenuItem *mnuLogout;
        wxMenuItem *mnuShowClosedPositions;

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
}

#endif
