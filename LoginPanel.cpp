#include <string>

#include <wx/wx.h>

#include "LoginPanel.h"
#include "MainFrame.h"
#include "Api.h"

// constructor ////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

LoginPanel::LoginPanel(wxWindow* parent)
    : wxPanel(parent, wxID_ANY)
{
    Setup();
}

// init ///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void LoginPanel::Setup()
{
    wxStaticText* lblName = new wxStaticText(this, wxID_ANY, "Email:");
    wxStaticText* lblPassword = new wxStaticText(this, wxID_ANY, "Password:");

    txtEmail = new wxTextCtrl(this, wxID_ANY);
    txtPassword = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);

    wxButton* btnLogin = new wxButton(this, ID_Login, "Login");
    btnLogin->Bind(wxEVT_BUTTON, &LoginPanel::OnLoginButtonClicked, this);

    wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);

    wxSizerFlags flagsLbl = wxSizerFlags().Border(wxALL, 25).Left();
    wxSizerFlags flagsInput = wxSizerFlags().Border(wxALL, 25).Expand();

    boxSizer->Add(lblName, flagsLbl);
    boxSizer->Add(txtEmail, flagsInput);
    boxSizer->Add(lblPassword, flagsLbl);
    boxSizer->Add(txtPassword, flagsInput);
    boxSizer->Add(btnLogin, flagsInput);

    SetSizer(boxSizer);
}

// event handlers /////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void LoginPanel::OnLoginButtonClicked(wxCommandEvent& event)
{
    try
    {
        Api::Login(txtEmail->GetValue().ToStdString(), txtPassword->GetValue().ToStdString());

        wxLogStatus("Login succeeded!");

        // allow MainFrame to detect login status change
        event.Skip();
    }
    catch (std::invalid_argument &e)
    {
        wxLogError(e.what());

        wxLogStatus("Login failed!");
    }
    catch (std::logic_error &e)
    {
        wxLogError(e.what());

        wxLogStatus("Login failed!");
    }
    catch (std::runtime_error &e)
    {
        wxLogError("Unknown error.");
        wxLogDebug(e.what());

        wxLogStatus("Login failed!");
    }
}
