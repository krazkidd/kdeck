#include <wx/wx.h>

#include "config/Config.hpp"
#include "ui/LoginDialog.hpp"
#include "ui/event.hpp"

namespace kdeck
{
    // constructor ////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    LoginDialog::LoginDialog(wxWindow* parent, wxWindowID winid, const wxString &title)
        : wxDialog(parent, winid, title)
    {
        Setup();
    }

    // init ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    void LoginDialog::Setup()
    {
        txtEmail = new wxTextCtrl(this, wxID_ANY);
        txtEmail->SetHint("Email");
        txtEmail->SetFocus();

        txtPassword = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
        txtPassword->SetHint("Password");

        chkRememberMe = new wxCheckBox(this, wxID_ANY, "Remember me");
        chkRememberMe->SetValue(false);

        wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);

        wxSizerFlags flagsInput = wxSizerFlags().Border(wxALL, 10).Expand();

        boxSizer->Add(txtEmail, flagsInput);
        boxSizer->Add(txtPassword, flagsInput);
        boxSizer->Add(chkRememberMe, flagsInput);

        wxSizer* szrButton = CreateButtonSizer(wxOK | wxCANCEL);
        if (szrButton)
        {
            boxSizer->Add(szrButton, wxSizerFlags().Center());
        }

        SetSizerAndFit(boxSizer);
    }

    void LoginDialog::UpdateStuff(const Config* config)
    {
        if (config->GetEmail().empty())
        {
            txtEmail->SetValue("");
            txtEmail->SetFocus();
            chkRememberMe->SetValue(false);
        }
        else
        {
            txtEmail->SetValue(config->GetEmail());
            txtPassword->SetFocus();
            chkRememberMe->SetValue(true);
        }
    }

    std::string LoginDialog::GetEmail() const
    {
        return txtEmail->GetValue().ToStdString();
    }

    std::string LoginDialog::GetPassword() const
    {
        return txtPassword->GetValue().ToStdString();
    }

    bool LoginDialog::GetRememberMe() const
    {
        return chkRememberMe->GetValue();
    }
}
