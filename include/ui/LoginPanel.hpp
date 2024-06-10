#ifndef LOGINPANEL_HPP
#define LOGINPANEL_HPP

#include <wx/wx.h>

class LoginPanel : public wxPanel
{
public:
    LoginPanel(wxWindow* parent, wxWindowID winid = wxID_ANY);

private:
    wxTextCtrl* txtEmail;
    wxTextCtrl* txtPassword;

    // init
    void Setup();

    // event handlers
    void OnLoginButtonClicked(wxCommandEvent& event);
};

#endif