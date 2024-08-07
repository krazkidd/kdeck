#include <algorithm>

#include <wx/string.h>
#include <wx/wx.h>

#include "api/Api.hpp"
#include "config/Config.hpp"
#include "ui/ExchangeAnnouncementsDialog.hpp"
#include "ui/ExchangeScheduleDialog.hpp"
#include "ui/ExchangeStatusDialog.hpp"
#include "ui/MainFrame.hpp"
#include "ui/LoginDialog.hpp"
#include "ui/PortfolioPanel.hpp"
#include "ui/event.hpp"

namespace kdeck
{
    // constructor ////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    MainFrame::MainFrame(wxWindow* parent, wxWindowID winid, const wxString &title)
        : wxFrame(parent, winid, title)
        , config{}
        , api{config.GetKalshiApiUrl(), config.GetSslTrustStoreDir()}
    {
        Setup();
    }

    // init ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    void MainFrame::Setup()
    {
        // NOTE: It appears to be important that we add the status bar (and possibly
        //       the menu bar) before we add a panel/sizer. It seems to change the
        //       dimensions of the panel/frame and messes with sizer logic.

        wxMenu *menuFile = new wxMenu;

        mnuLogin = menuFile->Append(ID_Login, "Login...", "Login");
        mnuLogout = menuFile->Append(ID_Logout, "Logout...", "Logout");

        mnuLogout->Enable(false);

        menuFile->AppendSeparator();
        menuFile->Append(wxID_EXIT);

        ///////////////////////////////////////////////////////////////////////////

        wxMenu *menuExchange = new wxMenu;

        menuExchange->Append(ID_Exchange_Announcements, "Announcements", "Announcements");
        menuExchange->Append(ID_Exchange_Schedule, "Schedule", "Schedule");
        menuExchange->Append(ID_Exchange_Status, "Status", "Status");

        ///////////////////////////////////////////////////////////////////////////

        wxMenu *menuView = new wxMenu;

        mnuShowClosedPositions = menuView->AppendCheckItem(ID_View_ShowClosedPositions, "Show Closed Positions", "Show Closed Positions");

        mnuShowClosedPositions->Enable(false);

        ///////////////////////////////////////////////////////////////////////////

        wxMenu *menuHelp = new wxMenu;
        menuHelp->Append(wxID_ABOUT);

        ///////////////////////////////////////////////////////////////////////////

        wxMenuBar *menuBar = new wxMenuBar;
        menuBar->Append(menuFile, "&File");
        menuBar->Append(menuExchange, "&Exchange");
        menuBar->Append(menuView, "&View");
        menuBar->Append(menuHelp, "&Help");

        SetMenuBar(menuBar);

        ///////////////////////////////////////////////////////////////////////////

        CreateStatusBar(3);
        ShowStatus(wxString::Format("Welcome to %s!", kProjectName));

        ///////////////////////////////////////////////////////////////////////////

        pnlPortfolio = new PortfolioPanel(this);

        SetMinSize(wxSize{400, 400});

        Bind(EVT_LOGIN, &MainFrame::OnLoginOrLogout, this);
        Bind(EVT_LOGOUT, &MainFrame::OnLoginOrLogout, this);
        Bind(EVT_API_ERROR, &MainFrame::OnApiError, this);
        Bind(wxEVT_IDLE, &MainFrame::OnIdleRunOnce, this);
        Bind(wxEVT_MENU, &MainFrame::OnMenuItemSelected, this);
        Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);
    }

    void MainFrame::UpdateStuff()
    {
        pnlPortfolio->UpdateStuff(&config, &api);

        mnuLogin->Enable(!api.IsLoggedIn());
        mnuLogout->Enable(api.IsLoggedIn());

        mnuShowClosedPositions->Enable(api.IsLoggedIn());
        mnuShowClosedPositions->Check(config.GetShowClosedPositions());
    }

    // helpers ////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    void MainFrame::DoLogin()
    {
        LoginDialog dlgLogin = LoginDialog(this);
        dlgLogin.UpdateStuff(&config);

        int answer = dlgLogin.ShowModal();

        if (answer == wxID_OK)
        {
            if (dlgLogin.GetRememberMe())
            {
                config.SetEmail(dlgLogin.GetEmail());
            }
            else
            {
                config.SetEmail(std::string{});
            }

            try
            {
                api.Login(dlgLogin.GetEmail(), dlgLogin.GetPassword());

                wxCommandEvent* evt = new wxCommandEvent(EVT_LOGIN);
                evt->SetEventObject(this);
                evt->SetString("Login succeeded!");
                QueueEvent(evt);
            }
            catch (const std::exception &e)
            {
                wxCommandEvent* evt = new wxCommandEvent(EVT_API_ERROR);
                evt->SetEventObject(this);
                evt->SetString("Login failed!");
                QueueEvent(evt);
            }
        }
    }

    void MainFrame::DoLogout()
    {
        int answer = wxMessageBox("Logout?", "Confirm", wxYES_NO | wxICON_QUESTION, this);

        if (answer == wxYES)
        {
            try
            {
                api.Logout();

                wxCommandEvent* evt = new wxCommandEvent(EVT_LOGOUT);
                evt->SetEventObject(this);
                evt->SetString("Logout succeeded!");
                QueueEvent(evt);
            }
            catch (const std::exception &e)
            {
                wxCommandEvent* evt = new wxCommandEvent(EVT_API_ERROR);
                evt->SetEventObject(this);
                evt->SetString("Logout failed!");
                QueueEvent(evt);
            }
        }
    }

    void MainFrame::DoShowExchangeAnnouncements()
    {
        ExchangeAnnouncementsDialog dlgAnnouncements = ExchangeAnnouncementsDialog(this);
        dlgAnnouncements.UpdateStuff(&api);
        dlgAnnouncements.ShowModal();
    }

    void MainFrame::DoShowExchangeSchedule()
    {
        ExchangeScheduleDialog dlgSchedule = ExchangeScheduleDialog(this);
        dlgSchedule.UpdateStuff(&api);
        dlgSchedule.ShowModal();
    }

    void MainFrame::DoShowExchangeStatus()
    {
        ExchangeStatusDialog dlgStatus = ExchangeStatusDialog(this);
        dlgStatus.UpdateStuff(&api);
        dlgStatus.ShowModal();
    }

    void MainFrame::ShowStatus(const wxString &msg)
    {
        SetStatusText(msg, 0);

        if (api.IsLoggedIn())
        {
            SetStatusText(L"🟢 Logged in", 2);
        }
        else
        {
            SetStatusText(L"🔴 Logged out", 2);
        }
    }

    // event handlers /////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    void MainFrame::OnLoginOrLogout(wxCommandEvent &event)
    {
        UpdateStuff();

        ShowStatus(event.GetString());
    }

    void MainFrame::OnApiError(wxCommandEvent &event)
    {
        ShowStatus(event.GetString());
    }

    void MainFrame::OnIdleRunOnce(wxIdleEvent &event)
    {
        // unbind this event handler so it only runs once
        Unbind(wxEVT_IDLE, &MainFrame::OnIdleRunOnce, this);

        DoLogin();
    }

    void MainFrame::OnMenuItemSelected(wxCommandEvent &event)
    {
        switch (event.GetId())
        {
            case ID_Login:
                DoLogin();

                break;
            case ID_Logout:
                DoLogout();

                break;
            case ID_Exchange_Announcements:
                DoShowExchangeAnnouncements();

                break;
            case ID_Exchange_Schedule:
                DoShowExchangeSchedule();

                break;
            case ID_Exchange_Status:
                DoShowExchangeStatus();

                break;
            case ID_View_ShowClosedPositions:
                config.SetShowClosedPositions(mnuShowClosedPositions->IsChecked());

                UpdateStuff();

                break;
            case wxID_ABOUT:
                wxMessageBox(wxString::Format("%s %s", kProjectName, kProjectVersion), wxString::Format("About %s", kProjectName), wxOK | wxICON_INFORMATION);

                break;
            case wxID_EXIT:
                Close();

                break;
        }
    }

    void MainFrame::OnClose(wxCloseEvent &event)
    {
        if (event.CanVeto() && api.IsLoggedIn())
        {
            int answer = wxMessageBox("Quit?", "Confirm", wxYES_NO | wxICON_QUESTION, this);

            if (answer == wxYES)
            {
                try
                {
                    api.Logout();
                }
                catch (const std::exception &e)
                {
                    // do nothing; we're closing anyway
                }

                Destroy();
            }
            else
            {
                event.Veto();
            }
        }
        else
        {
            Destroy();
        }
    }
}
