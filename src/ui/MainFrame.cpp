#include <algorithm>
#include <wx/wx.h>

#include "api/Api.hpp"
#include "ui/MainFrame.hpp"
#include "ui/LoginDialog.hpp"
#include "ui/PortfolioPanel.hpp"
#include "ui/event.hpp"

// constructor ////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

MainFrame::MainFrame(wxWindow* parent, wxWindowID winid, const wxString &title)
    : wxFrame(parent, winid, title)
{
    Setup();

    Bind(EVT_LOGIN, &MainFrame::OnLoginOrLogout, this);
    Bind(EVT_LOGOUT, &MainFrame::OnLoginOrLogout, this);
    Bind(EVT_API_ERROR, &MainFrame::OnApiError, this);
    Bind(wxEVT_MENU, &MainFrame::OnLoginMenuItemSelected, this, ID_Login);
    Bind(wxEVT_MENU, &MainFrame::OnLogoutMenuItemSelected, this, ID_Logout);
    Bind(wxEVT_MENU, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);

    Bind(wxEVT_IDLE, &MainFrame::OnIdle, this);
}

// init ///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void MainFrame::Setup()
{
    // NOTE: It seems to be important that we add the status bar (and possibly
    //       the menu bar) before we add a panel/sizer. It seems to change the
    //       dimensions of the panel/frame and messes with sizer logic.

    wxMenu *menuFile = new wxMenu;

    loginMenuItem = menuFile->Append(ID_Login, "Login...", "Login");
    logoutMenuItem = menuFile->Append(ID_Logout, "Logout...", "Logout");

    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar(menuBar);

    CreateStatusBar();
    SetStatusText("Welcome to kdeck!");
}

void MainFrame::UpdateStuff()
{
    if (Api::IsLoggedIn())
    {
        wxPanel* panel = new PortfolioPanel(this);
        panel->GetSizer()->SetSizeHints(this);

        SetMinSize(wxSize{400, 400});

        loginMenuItem->Enable(false);
        logoutMenuItem->Enable(true);
    }
    else
    {
        loginMenuItem->Enable(true);
        logoutMenuItem->Enable(false);

        LoginDialog dlgLogin = LoginDialog(this);
        if (dlgLogin.ShowModal() == wxID_OK)
        {
            wxCommandEvent* loginEvent = nullptr;

            try
            {
                Api::Login(dlgLogin.GetEmail(), dlgLogin.GetPassword());

                loginEvent = new wxCommandEvent(EVT_LOGIN);
                loginEvent->SetString("Login succeeded!");
            }
            catch (std::exception &e)
            {
                std::cerr << e.what() << std::endl;

                loginEvent = new wxCommandEvent(EVT_API_ERROR);
                loginEvent->SetString("Login failed!");
            }

            loginEvent->SetEventObject(this);

            QueueEvent(loginEvent);
        }
    }
}

// event handlers /////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void MainFrame::OnLoginOrLogout(wxCommandEvent &event)
{
    UpdateStuff();

    wxLogStatus(event.GetString());
}

void MainFrame::OnApiError(wxCommandEvent &event)
{
    wxLogStatus(event.GetString());
}

void MainFrame::OnIdle(wxIdleEvent &event)
{
    Unbind(wxEVT_IDLE, &MainFrame::OnIdle, this);

    UpdateStuff();
}

void MainFrame::OnLoginMenuItemSelected(wxCommandEvent &event)
{
    UpdateStuff();
}

void MainFrame::OnLogoutMenuItemSelected(wxCommandEvent &event)
{
    int answer = wxMessageBox("Logout?", "Confirm", wxYES_NO | wxICON_QUESTION, this);

    if (answer == wxYES)
    {
        wxCommandEvent* logoutEvent = nullptr;

        try
        {
            Api::Logout();

            logoutEvent = new wxCommandEvent(EVT_LOGOUT);
            logoutEvent->SetString("Logout succeeded!");
        }
        catch (std::exception &e)
        {
            std::cerr << e.what() << std::endl;

            logoutEvent = new wxCommandEvent(EVT_API_ERROR);
            logoutEvent->SetString("Logout failed!");
        }

        logoutEvent->SetEventObject(this);

        QueueEvent(logoutEvent);
    }
}

void MainFrame::OnAbout(wxCommandEvent &event)
{
    wxMessageBox("This is kdeck", "About kdeck", wxOK | wxICON_INFORMATION);
}

void MainFrame::OnExit(wxCommandEvent &event)
{
    Close();
}

void MainFrame::OnClose(wxCloseEvent &event)
{
    if (event.CanVeto() && Api::IsLoggedIn())
    {
        int answer = wxMessageBox("Quit?", "Confirm", wxYES_NO | wxICON_QUESTION, this);

        if (answer == wxYES)
        {
            try
            {
                Api::Logout();
            }
            catch (std::exception &e)
            {
                std::cerr << e.what() << std::endl;
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
