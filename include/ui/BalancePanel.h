#ifndef BALANCEPANEL_H
#define BALANCEPANEL_H

#include <wx/wx.h>

#include "ui/StaticCurrency.h"

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