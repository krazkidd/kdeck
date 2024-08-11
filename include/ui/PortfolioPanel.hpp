#ifndef PORTFOLIOPANEL_HPP
#define PORTFOLIOPANEL_HPP

#include <wx/wx.h>

#include "PortfolioPanel.h" // wxfb

namespace kdeck
{
    class Api;
    class BalancePanel;
    class Config;

    class PortfolioPanel : public wxfb::PortfolioPanel
    {
    public:
        PortfolioPanel(wxWindow* parent, wxWindowID winid = wxID_ANY);

        void UpdateStuff(const Config* config, Api* api);
    };
}

#endif
