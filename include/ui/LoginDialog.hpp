#ifndef LOGINDIALOG_HPP
#define LOGINDIALOG_HPP

#include <wx/wx.h>

class LoginDialog : public wxDialog
{
public:
    LoginDialog(wxWindow* parent, wxWindowID winid = wxID_ANY, const wxString &title = "Login");

    std::string GetEmail() const;
    std::string GetPassword() const;

private:
    wxTextCtrl* txtEmail;
    wxTextCtrl* txtPassword;

    // init
    void Setup();
};

#endif
