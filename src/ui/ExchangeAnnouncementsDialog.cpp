#include <wx/wx.h>

#include "App.h" // wxfb

#include "api/Api.hpp"
#include "ui/ExchangeAnnouncementsDialog.hpp"
#include "ui/event.hpp"

namespace kdeck
{
    class ExchangeAnnouncementsResponse;

    // constructor ////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    ExchangeAnnouncementsDialog::ExchangeAnnouncementsDialog(wxWindow* parent, wxWindowID winid)
        : wxfb::ExchangeAnnouncementsDialog(parent, winid)
    {

    }

    // init ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    void ExchangeAnnouncementsDialog::UpdateStuff(Api* api)
    {
        fgszrAnnouncements->Clear();

        try
        {
            std::shared_ptr<ExchangeAnnouncementsResponse> announcements = api->GetExchangeAnnouncements();

            bool hasAnnouncements = !announcements->announcements->empty();

            fgszrAnnouncements->Show(hasAnnouncements);
            lblNoAnnouncements->Show(!hasAnnouncements);

            for (auto announcement : *announcements->announcements)
            {
                wxSizerFlags flagsLbl = wxSizerFlags().Border(wxLEFT, 10).CenterVertical();

                fgszrAnnouncements->Add(new wxStaticText(this, wxID_ANY, announcement->delivery_time->c_str()), flagsLbl);
                fgszrAnnouncements->Add(new wxStaticText(this, wxID_ANY, announcement->status->c_str()), flagsLbl);
                fgszrAnnouncements->Add(new wxStaticText(this, wxID_ANY, announcement->type->c_str()), flagsLbl);
                fgszrAnnouncements->Add(new wxStaticText(this, wxID_ANY, announcement->message->c_str()), flagsLbl);
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
