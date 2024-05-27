#ifndef PORTFOLIOPANEL_H
#define PORTFOLIOPANEL_H

#include <wx/wx.h>

class PortfolioPanel : public wxPanel
{
public:
    PortfolioPanel(wxWindow* parent);

private:
    wxStaticText* lblBalanceAmount;

    // init
    void Setup();
    void Update();
};

#endif