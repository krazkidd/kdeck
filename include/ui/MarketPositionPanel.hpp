#ifndef MARKETPOSITIONPANEL_HPP
#define MARKETPOSITIONPANEL_HPP

#include <memory>

#include <wx/wx.h>

namespace kdeck
{
    class MarketPosition;

    class MarketPositionPanel : public wxPanel
    {
    public:
        MarketPositionPanel(wxWindow* parent, wxWindowID winid, std::shared_ptr<MarketPosition> market);

    private:
        std::shared_ptr<MarketPosition> market;

        // init
        void Setup();
    };
}

#endif
