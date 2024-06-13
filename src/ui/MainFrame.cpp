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

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar(menuBar);

    CreateStatusBar();
    SetStatusText("Welcome to kdeck!");

    pnlPortfolio = new PortfolioPanel(this);
    pnlPortfolio->GetSizer()->SetSizeHints(this);

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
    pnlPortfolio->UpdateStuff();

    mnuLogin->Enable(!Api::IsLoggedIn());
    mnuLogout->Enable(Api::IsLoggedIn());
}

// helpers ////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void MainFrame::DoLogin()
{
    LoginDialog dlgLogin = LoginDialog(this);
    int answer = dlgLogin.ShowModal();

    if (answer == wxID_OK)
    {
        try
        {
            Api::Login(dlgLogin.GetEmail(), dlgLogin.GetPassword());

            wxCommandEvent* evt = new wxCommandEvent(EVT_LOGIN);
            evt->SetEventObject(this);
            evt->SetString("Login succeeded!");
            QueueEvent(evt);
        }
        catch (std::exception &e)
        {
            std::cerr << e.what() << std::endl;

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
            Api::Logout();

            wxCommandEvent* evt = new wxCommandEvent(EVT_LOGOUT);
            evt->SetEventObject(this);
            evt->SetString("Logout succeeded!");
            QueueEvent(evt);
        }
        catch (std::exception &e)
        {
            std::cerr << e.what() << std::endl;

            wxCommandEvent* evt = new wxCommandEvent(EVT_API_ERROR);
            evt->SetEventObject(this);
            evt->SetString("Logout failed!");
            QueueEvent(evt);
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
        case wxID_ABOUT:
            wxMessageBox("This is kdeck", "About kdeck", wxOK | wxICON_INFORMATION);

            break;
        case wxID_EXIT:
            Close();

            break;
    }
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
