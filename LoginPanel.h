#ifndef LOGINPANEL_H
#define LOGINPANEL_H

#include <string>

#include <wx/wx.h>

class LoginPanel : public wxPanel
{
public:
    LoginPanel(wxWindow* parent);

private:
    wxTextCtrl* txtEmail;
    wxTextCtrl* txtPassword;

    // init
    void AddControls();

    // API requests
    std::string RequestLoginToken(std::string email, std::string password);

    // event handlers
    void OnLoginButtonClicked(wxCommandEvent& event);
};

#endif