#ifndef MARKETPOSITIONPANEL_H
#define MARKETPOSITIONPANEL_H

#include <wx/wx.h>

#include "api/types.hpp"

class MarketPositionPanel : public wxPanel
{
public:
    MarketPositionPanel(wxWindow* parent, wxWindowID winid, PortfolioPositionsResponse::MarketPosition* market);

private:
    //TODO this is a pointer, should be a reference?
    PortfolioPositionsResponse::MarketPosition* market;

    // init
    void Setup();
};

#endif