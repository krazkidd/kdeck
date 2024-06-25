#include <wx/wx.h>

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

        txtPassword = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
        txtPassword->SetHint("Password");

        wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);

        wxSizerFlags flagsInput = wxSizerFlags().Border(wxALL, 10).Expand();

        boxSizer->Add(txtEmail, flagsInput);
        boxSizer->Add(txtPassword, flagsInput);

        wxSizer* szrButton = CreateButtonSizer(wxOK | wxCANCEL);
        if (szrButton)
        {
            boxSizer->Add(szrButton);
        }

        if (txtEmail->IsEmpty())
        {
            txtEmail->SetFocus();
        }
        else
        {
            txtPassword->SetFocus();
        }

        SetSizerAndFit(boxSizer);
    }

    std::string LoginDialog::GetEmail() const
    {
        return txtEmail->GetValue().ToStdString();
    }

    std::string LoginDialog::GetPassword() const
    {
        return txtPassword->GetValue().ToStdString();
    }
}
