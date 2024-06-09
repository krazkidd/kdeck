#ifndef BALANCEPANEL_H
#define BALANCEPANEL_H

#include <wx/wx.h>

class BalancePanel : public wxPanel
{
public:
    BalancePanel(wxWindow* parent, wxWindowID winid = wxID_ANY);

    void UpdateStuff();

private:
    wxStaticText* lblBalanceAmount;

    // init
    void Setup();
};

#endif