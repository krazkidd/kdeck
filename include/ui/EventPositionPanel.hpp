#ifndef EVENTTPOSITIONPANEL_HPP
#define EVENTTPOSITIONPANEL_HPP

#include <wx/wx.h>

#include "api/types.hpp"

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
