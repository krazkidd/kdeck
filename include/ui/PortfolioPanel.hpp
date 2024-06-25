#ifndef PORTFOLIOPANEL_HPP
#define PORTFOLIOPANEL_HPP

#include <wx/wx.h>

namespace kdeck
{
    class Api;
    class BalancePanel;

    class PortfolioPanel : public wxScrolledWindow
    {
    public:
        PortfolioPanel(wxWindow* parent, wxWindowID winid = wxID_ANY);

        void UpdateStuff(Api* api);

    private:
        BalancePanel* pnlBalance;
        wxPanel* pnlPositions;

        // init
        void Setup();
    };
}

#endif
