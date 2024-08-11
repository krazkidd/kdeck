#ifndef MAINFRAME_HPP
#define MAINFRAME_HPP

#include <wx/wx.h>

#include "App.h" // wxfb

#include "app_config.hpp"
#include "api/Api.hpp"
#include "config/Config.hpp"

namespace kdeck
{
    class MainFrame : public wxfb::MainFrame
    {
    public:
        MainFrame(wxWindow* parent = nullptr, wxWindowID winid = wxID_ANY, const wxString &title = std::string{kProjectName});

        void UpdateStuff();

    private:
        // config must be ordered before api (see constructor in MainFrame.cpp)
        Config config;
        Api api;

        bool isLoginDialogShownOnce = false;

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
        void OnShow(wxShowEvent &event) override;
        void OnMenuItemSelected(wxCommandEvent& event) override;
        void OnClose(wxCloseEvent& event) override;
    };
}

#endif
