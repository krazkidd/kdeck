#include <wx/wx.h>

#include "api/Api.hpp"
#include "ui/ExchangeAnnouncementsDialog.hpp"
#include "ui/event.hpp"

namespace kdeck
{
    class ExchangeAnnouncementsResponse;

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

    void ExchangeAnnouncementsDialog::UpdateStuff(Api* api)
    {
        boxSizer->Clear();

        try
        {
            std::shared_ptr<ExchangeAnnouncementsResponse> announcements = api->GetExchangeAnnouncements();

            if (announcements->announcements->empty())
            {
                boxSizer->Add(new wxStaticText(this, wxID_ANY, "No announcements."));
            }
            else
            {
                wxSizerFlags flags = wxSizerFlags().Border(wxUP | wxDOWN, 10).Expand();

                for (auto announcement : *announcements->announcements)
                {
                    wxBoxSizer* szr = new wxBoxSizer(wxHORIZONTAL);

                    szr->Add(new wxStaticText(this, wxID_ANY, announcement->delivery_time->c_str()));
                    szr->Add(new wxStaticText(this, wxID_ANY, announcement->status->c_str()));
                    szr->Add(new wxStaticText(this, wxID_ANY, announcement->type->c_str()));
                    szr->Add(new wxStaticText(this, wxID_ANY, announcement->message->c_str()));

                    boxSizer->Add(szr, flags);
                }
            }
        }
        catch (const std::exception &e)
        {
            wxCommandEvent* evt = new wxCommandEvent(EVT_API_ERROR);
            evt->SetEventObject(this);
            evt->SetString("Exchange announcements failed!");
            QueueEvent(evt);
        }
    }
}
