#include <wx/wx.h>

#include "ui/MainFrame.h"
#include "ui/LoginPanel.h"
#include "ui/PortfolioPanel.h"
#include "api/Api.h"

// constructor ////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

MainFrame::MainFrame()
    : wxFrame(nullptr, wxID_ANY, "kdeck")
{
    Setup();
    Update();

    Bind(wxEVT_BUTTON, &MainFrame::OnLoginButtonClicked, this);
    Bind(wxEVT_MENU, &MainFrame::OnLogoutMenuItemSelected, this, ID_Logout);
    Bind(wxEVT_MENU, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MainFrame::OnExit, this, wxID_EXIT);
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
        logoutMenuItem->Enable(true);

        PortfolioPanel* panel = new PortfolioPanel(this);
        panel->GetSizer()->SetSizeHints(this);
    }
    else
    {
        logoutMenuItem->Enable(false);

        LoginPanel* panel = new LoginPanel(this);
        panel->GetSizer()->SetSizeHints(this);
    }
}

// event handlers /////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//TODO this should be implemented as a custom event
void MainFrame::OnLoginButtonClicked(wxCommandEvent &event)
{
    if (event.GetId() == ID_Login)
    {
        Update();
    }
}

void MainFrame::OnLogoutMenuItemSelected(wxCommandEvent &event)
{
    int answer = wxMessageBox("Logout?", "Confirm", wxYES_NO | wxICON_QUESTION, this);

    if (answer == wxYES)
    {
        try
        {
            Api::Logout();

            wxLogStatus("Logout succeeded!");
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

        Update();
    }
}

void MainFrame::OnAbout(wxCommandEvent &event)
{
    wxMessageBox("This is kdeck", "About kdeck", wxOK | wxICON_INFORMATION);
}

void MainFrame::OnExit(wxCommandEvent &event)
{
    if (Api::IsLoggedIn())
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
        }
    }

    Close(true);
}
