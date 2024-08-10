#ifndef ENUM_HPP
#define ENUM_HPP

#include <wx/wx.h>

namespace kdeck
{
    enum
    {
        ID_Login = wxID_HIGHEST + 1,
        ID_Logout = wxID_HIGHEST + 2,
        ID_Exchange_Announcements = wxID_HIGHEST + 3,
        ID_Exchange_Schedule = wxID_HIGHEST + 4,
        ID_Exchange_Status = wxID_HIGHEST + 5,
        ID_View_ShowClosedPositions = wxID_HIGHEST + 6,
    };
}

#endif
