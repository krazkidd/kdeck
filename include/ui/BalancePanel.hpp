#ifndef BALANCEPANEL_HPP
#define BALANCEPANEL_HPP

#include <wx/wx.h>

namespace kdeck
{
    class Api;
    class StaticCurrency;

    class BalancePanel : public wxPanel
    {
    public:
        BalancePanel(wxWindow* parent, wxWindowID winid = wxID_ANY, double balance = 0.0);

        void UpdateStuff(Api* api);

    private:
        StaticCurrency* lblBalanceAmount;

        // init
        void Setup();
    };
}

#endif
