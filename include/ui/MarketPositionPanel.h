#ifndef MARKETPOSITIONPANEL_H
#define MARKETPOSITIONPANEL_H

#include <wx/wx.h>

#include "api/types.h"

class MarketPositionPanel : public wxPanel
{
public:
    MarketPositionPanel(wxWindow* parent, PortfolioPositionsResponse::MarketPosition* position);

private:
    //TODO this is a pointer, should be a reference?
    PortfolioPositionsResponse::MarketPosition* position;

    // init
    void Setup();
};

#endif