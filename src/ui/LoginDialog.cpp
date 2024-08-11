#include <wx/wx.h>

#include "App.h" // wxfb

#include "config/Config.hpp"
#include "ui/LoginDialog.hpp"
#include "ui/event.hpp"

namespace kdeck
{
    // constructor ////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    LoginDialog::LoginDialog(wxWindow* parent, wxWindowID winid)
        : wxfb::LoginDialog(parent, winid)
    {

    }

    // init ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

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
