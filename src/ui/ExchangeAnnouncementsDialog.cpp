#include <wx/wx.h>

#include "api/Api.hpp"
#include "ui/ExchangeAnnouncementsDialog.hpp"
#include "ui/event.hpp"

// constructor ////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

ExchangeAnnouncementsDialog::ExchangeAnnouncementsDialog(wxWindow* parent, wxWindowID winid, const wxString &title)
    : wxDialog(parent, winid, title)
{
    Setup();
}

// init ///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void ExchangeAnnouncementsDialog::Setup()
{
    boxSizer = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer* szr = new wxBoxSizer(wxVERTICAL);

    szr->Add(boxSizer, wxSizerFlags().Border(wxALL, 10).Expand());

    wxSizer* szrButton = CreateButtonSizer(wxOK);
    if (szrButton)
    {
        szr->Add(szrButton, wxSizerFlags().Center());
    }

    SetSizerAndFit(szr);
}

void ExchangeAnnouncementsDialog::UpdateStuff()
{
    boxSizer->Clear();

    try
    {
        ExchangeAnnouncementsResponse announcements = Api::GetExchangeAnnouncements();

        wxSizerFlags flags = wxSizerFlags().Border(wxALL, 10); //.Expand();

        if (announcements.announcements.empty())
        {
            boxSizer->Add(new wxStaticText(this, wxID_ANY, "No announcements."), flags);
        }
        else
        {
            for (auto announcement : announcements.announcements)
            {
                wxBoxSizer* szr = new wxBoxSizer(wxHORIZONTAL);

                //TODO need to stringify/localize time
                //szr->Add(new wxStaticText(this, wxID_ANY, announcement.delivery_time), flags);
                szr->Add(new wxStaticText(this, wxID_ANY, announcement.status), flags);
                szr->Add(new wxStaticText(this, wxID_ANY, announcement.type), flags);
                szr->Add(new wxStaticText(this, wxID_ANY, announcement.message), flags);
            }
        }
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;

        wxCommandEvent* evt = new wxCommandEvent(EVT_API_ERROR);
        evt->SetEventObject(this);
        evt->SetString("Exchange announcements failed!");
        QueueEvent(evt);
    }
}

bool ExchangeAnnouncementsDialog::Show(bool show)
{
    UpdateStuff();

    return wxDialog::Show(show);
}
