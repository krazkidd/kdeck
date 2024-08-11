#ifndef LOGINDIALOG_HPP
#define LOGINDIALOG_HPP

#include <wx/wx.h>

#include "App.h" // wxfb

namespace kdeck
{
    class Config;

    class LoginDialog : public wxfb::LoginDialog
    {
    public:
        LoginDialog(wxWindow* parent, wxWindowID winid = wxID_ANY);

        void UpdateStuff(const Config* config);

        std::string GetEmail() const;
        std::string GetPassword() const;

        bool GetRememberMe() const;
    };
}

#endif
