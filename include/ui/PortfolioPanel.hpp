#ifndef PORTFOLIOPANEL_HPP
#define PORTFOLIOPANEL_HPP

#include <wx/wx.h>

#include "ui/BalancePanel.hpp"

class PortfolioPanel : public wxScrolledWindow
{
public:
    PortfolioPanel(wxWindow* parent, wxWindowID winid = wxID_ANY);

private:
    BalancePanel* pnlBalance;
    wxPanel* pnlPositions;

    // init
    void Setup();
    void UpdateStuff();
};

#endif