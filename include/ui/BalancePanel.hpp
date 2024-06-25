#ifndef BALANCEPANEL_HPP
#define BALANCEPANEL_HPP

#include <wx/wx.h>

class Api;
class StaticCurrency;

class BalancePanel : public wxPanel
{
public:
    BalancePanel(Api* api, wxWindow* parent, wxWindowID winid = wxID_ANY);

    void UpdateStuff();

private:
    Api* api;

    StaticCurrency* lblBalanceAmount;

    // init
    void Setup();
};

#endif
