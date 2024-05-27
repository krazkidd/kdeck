#ifndef LOGINPANEL_H
#define LOGINPANEL_H

#include <wx/wx.h>

class LoginPanel : public wxPanel
{
public:
    LoginPanel(wxWindow* parent);

private:
    wxTextCtrl* txtEmail;
    wxTextCtrl* txtPassword;

    // init
    void Setup();

    // event handlers
    void OnLoginButtonClicked(wxCommandEvent& event);
};

#endif