#ifndef EVENTTPOSITIONPANEL_HPP
#define EVENTTPOSITIONPANEL_HPP

#include <memory>

#include <wx/wx.h>

namespace kdeck
{
    class EventPosition;

    class EventPositionPanel : public wxPanel
    {
    public:
        EventPositionPanel(wxWindow* parent, wxWindowID winid, std::shared_ptr<EventPosition> event);

    private:
        std::shared_ptr<EventPosition> event;

        // init
        void Setup();
    };
}

#endif
