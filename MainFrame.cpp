#include <wx/wx.h>

#include "MainFrame.h"
#include "LoginPanel.h"

// constructor ////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

MainFrame::MainFrame()
    : wxFrame(nullptr, wxID_ANY, "kdeck")
{
    // NOTE: It seems to be important that we add the status bar (and possibly
    //       the menu bar) before we add a panel. It seems to change the dimensions
    //       of the panel/frame and messes with sizer logic.

    AddMenuBar();
    CreateStatusBar();
    SetStatusText("Welcome to kdeck!");

    AddLoginPanel();

    Bind(wxEVT_MENU, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MainFrame::OnExit, this, wxID_EXIT);
}

// init ///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void MainFrame::AddMenuBar()
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(wxID_EXIT);

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar(menuBar);
}

void MainFrame::AddLoginPanel()
{
    LoginPanel* loginPanel = new LoginPanel(this);
    loginPanel->GetSizer()->SetSizeHints(this);
}

// event handlers /////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is kdeck", "About kdeck", wxOK | wxICON_INFORMATION);
}

void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}
