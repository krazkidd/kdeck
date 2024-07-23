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
        //TODO? messages have arbitrary length, so we should probably set a max size;
        //      wxWidgets complains if max size is less than the sizer's minimum size
        //      (look in git log for how I reconciled these previously)
        //SetMaxSize(wxSize{800, 0});
    }

    void ExchangeAnnouncementsDialog::UpdateStuff(Api* api)
    {
        boxSizer->Clear();

        try
        {
            std::shared_ptr<ExchangeAnnouncementsResponse> announcements = api->GetExchangeAnnouncements();

            if (announcements->announcements->empty())
            {
                boxSizer->Add(new wxStaticText(this, wxID_ANY, "No announcements."), wxSizerFlags().Center());
            }
            else
            {
                wxSizerFlags flags = wxSizerFlags().Border(wxUP | wxDOWN, 10).Expand();

                for (auto announcement : *announcements->announcements)
                {
                    wxBoxSizer* szr = new wxBoxSizer(wxHORIZONTAL);

                    wxSizerFlags flagsLbl = wxSizerFlags().Border(wxLEFT, 10).CenterVertical();

                    szr->Add(new wxStaticText(this, wxID_ANY, announcement->delivery_time->c_str()), flagsLbl);
                    szr->Add(new wxStaticText(this, wxID_ANY, announcement->status->c_str()), flagsLbl);
                    szr->Add(new wxStaticText(this, wxID_ANY, announcement->type->c_str()), flagsLbl);
                    szr->Add(new wxStaticText(this, wxID_ANY, announcement->message->c_str()), flagsLbl);

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
