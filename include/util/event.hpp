#ifndef EVENT_HPP
#define EVENT_HPP

#include <wx/wx.h>

wxDECLARE_EVENT(EVT_LOGIN, wxCommandEvent);
wxDECLARE_EVENT(EVT_LOGOUT, wxCommandEvent);
wxDECLARE_EVENT(EVT_API_ERROR, wxCommandEvent);

#endif