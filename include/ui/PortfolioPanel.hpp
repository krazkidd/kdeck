#ifndef PORTFOLIOPANEL_HPP
#define PORTFOLIOPANEL_HPP

#include <wx/wx.h>

class Api;
class BalancePanel;

class PortfolioPanel : public wxScrolledWindow
{
public:
    PortfolioPanel(Api* api, wxWindow* parent, wxWindowID winid = wxID_ANY);

    void UpdateStuff();

private:
    Api* api;

    BalancePanel* pnlBalance;
    wxPanel* pnlPositions;

    // init
    void Setup();
};

#endif
