#include <string>

#include <wx/wx.h>

#include "ui/LoginPanel.h"
#include "ui/MainFrame.h"
#include "api/Api.h"
#include "util/event.h"

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
    try
    {
        Api::Login(txtEmail->GetValue().ToStdString(), txtPassword->GetValue().ToStdString());

        wxCommandEvent* event = new wxCommandEvent(EVT_LOGIN);

        event->SetEventObject(this);

        QueueEvent(event);
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
