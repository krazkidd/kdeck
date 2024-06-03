#ifndef EVENTTPOSITIONPANEL_H
#define EVENTTPOSITIONPANEL_H

#include <wx/wx.h>

#include "api/types.h"

class EventPositionPanel : public wxPanel
{
public:
    EventPositionPanel(wxWindow* parent, wxWindowID winid, PortfolioPositionsResponse::EventPosition* event);

private:
    //TODO these are pointers, should be references?
    PortfolioPositionsResponse::EventPosition* event;

    // init
    void Setup();
};

#endif