#include <algorithm>
#include <wx/wx.h>

#include "ui/MainFrame.h"
#include "ui/LoginPanel.h"
#include "ui/PortfolioPanel.h"
#include "api/Api.h"
#include "util/event.h"

// constructor ////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

MainFrame::MainFrame()
    : wxFrame(nullptr, wxID_ANY, "kdeck")
{
    Setup();
    Update();

    Bind(EVT_LOGIN, &MainFrame::OnLogin, this);
    Bind(EVT_LOGOUT, &MainFrame::OnLogout, this);
    Bind(wxEVT_MENU, &MainFrame::OnLogoutMenuItemSelected, this, ID_Logout);
    Bind(wxEVT_MENU, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);
}

// init ///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void MainFrame::Setup()
{
    // NOTE: It seems to be important that we add the status bar (and possibly
    //       the menu bar) before we add a panel/sizer. It seems to change the
    //       dimensions of the panel/frame and messes with sizer logic.

    wxMenu *menuFile = new wxMenu;
    logoutMenuItem = menuFile->Append(ID_Logout, "&Logout...\tCtrl+L", "Logout");
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

void MainFrame::Update()
{
    DestroyChildren();

    if (Api::IsLoggedIn())
    {
        wxPanel* panel = new PortfolioPanel(this);
        panel->GetSizer()->SetSizeHints(this);

        SetMinSize(wxSize{400, 400});

        logoutMenuItem->Enable(true);
    }
    else
    {
        wxPanel* panel = new LoginPanel(this);
        panel->GetSizer()->SetSizeHints(this);

        wxSize minSize = GetMinSize();

        SetMinSize(wxSize{std::max(400, minSize.GetX()), std::max(400, minSize.GetY())});

        logoutMenuItem->Enable(false);
    }
}

// event handlers /////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void MainFrame::OnLogin(wxCommandEvent &event)
{
    Update();

    wxLogStatus("Login succeeded!");
}

void MainFrame::OnLogout(wxCommandEvent &event)
{
    Update();

    wxLogStatus("Logout succeeded!");
}

void MainFrame::OnLogoutMenuItemSelected(wxCommandEvent &event)
{
    int answer = wxMessageBox("Logout?", "Confirm", wxYES_NO | wxICON_QUESTION, this);

    if (answer == wxYES)
    {
        try
        {
            Api::Logout();

            wxCommandEvent* event = new wxCommandEvent(EVT_LOGOUT);

            event->SetEventObject(this);

            QueueEvent(event);
        }
        catch (std::logic_error &e)
        {
            wxLogError(e.what());

            wxLogStatus("Logout failed!");
        }
        catch (std::runtime_error &e)
        {
            wxLogError("Unknown error.");
            wxLogDebug(e.what());

            wxLogStatus("Logout failed!");
        }
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
            catch (std::logic_error &e)
            {
                wxLogError(e.what());

                wxLogStatus("Logout failed!");
            }
            catch (std::runtime_error &e)
            {
                wxLogError("Unknown error.");
                wxLogDebug(e.what());

                wxLogStatus("Logout failed!");
            }
            catch (std::exception &e)
            {
                wxLogError("Unknown error.");
                wxLogDebug(e.what());

                wxLogStatus("Logout failed!");
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
