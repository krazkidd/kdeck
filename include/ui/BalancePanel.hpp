#ifndef BALANCEPANEL_HPP
#define BALANCEPANEL_HPP

#include <wx/wx.h>

class StaticCurrency;

class BalancePanel : public wxPanel
{
public:
    BalancePanel(wxWindow* parent, wxWindowID winid = wxID_ANY);

    void UpdateStuff();

private:
    StaticCurrency* lblBalanceAmount;

    // init
    void Setup();
};

#endif