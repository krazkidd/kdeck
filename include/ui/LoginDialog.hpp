#ifndef LOGINDIALOG_HPP
#define LOGINDIALOG_HPP

#include <wx/wx.h>

namespace kdeck
{
    class Config;

    class LoginDialog : public wxDialog
    {
    public:
        LoginDialog(wxWindow* parent, wxWindowID winid = wxID_ANY, const wxString &title = "Login");

        void UpdateStuff(const Config* config);

        std::string GetEmail() const;
        std::string GetPassword() const;

        bool GetRememberMe() const;

    private:
        wxTextCtrl* txtEmail;
        wxTextCtrl* txtPassword;
        wxCheckBox* chkRememberMe;

        // init
        void Setup();
    };
}

#endif
