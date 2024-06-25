#include "ui/event.hpp"

namespace kdeck
{
    wxDEFINE_EVENT(EVT_LOGIN, wxCommandEvent);
    wxDEFINE_EVENT(EVT_LOGOUT, wxCommandEvent);
    wxDEFINE_EVENT(EVT_API_ERROR, wxCommandEvent);
}
