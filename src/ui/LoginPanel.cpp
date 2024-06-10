#include <wx/wx.h>

#include "api/Api.hpp"
#include "ui/LoginPanel.hpp"
#include "util/event.hpp"

// constructor ////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

LoginPanel::LoginPanel(wxWindow* parent, wxWindowID winid)
    : wxPanel(parent, winid)
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

    wxButton* btnLogin = new wxButton(this, wxID_ANY, "Login");
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

void LoginPanel::OnLoginButtonClicked(wxCommandEvent &event)
{
    wxCommandEvent* loginEvent = nullptr;

    try
    {
        Api::Login(txtEmail->GetValue().ToStdString(), txtPassword->GetValue().ToStdString());

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
