#include <wx/string.h>
#include <wx/wx.h>

#include "api/Api.hpp"
#include "ui/ExchangeScheduleDialog.hpp"
#include "ui/event.hpp"

namespace kdeck
{
    class ExchangeScheduleResponse;

    // constructor ////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    ExchangeScheduleDialog::ExchangeScheduleDialog(wxWindow* parent, wxWindowID winid, const wxString &title)
        : wxDialog(parent, winid, title)
    {
        Setup();
    }

    // init ///////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////

    void ExchangeScheduleDialog::Setup()
    {
        wxStaticText* lblSunday = new wxStaticText(this, wxID_ANY, "Sunday:");
        lblSundaySchedule = new wxStaticText(this, wxID_ANY, "");

        wxStaticText* lblMonday = new wxStaticText(this, wxID_ANY, "Monday:");
        lblMondaySchedule = new wxStaticText(this, wxID_ANY, "");

        wxStaticText* lblTuesday = new wxStaticText(this, wxID_ANY, "Tuesday:");
        lblTuesdaySchedule = new wxStaticText(this, wxID_ANY, "");

        wxStaticText* lblWednesday = new wxStaticText(this, wxID_ANY, "Wednesday:");
        lblWednesdaySchedule = new wxStaticText(this, wxID_ANY, "");

        wxStaticText* lblThursday = new wxStaticText(this, wxID_ANY, "Thursday:");
        lblThursdaySchedule = new wxStaticText(this, wxID_ANY, "");

        wxStaticText* lblFriday = new wxStaticText(this, wxID_ANY, "Friday:");
        lblFridaySchedule = new wxStaticText(this, wxID_ANY, "");

        wxStaticText* lblSaturday = new wxStaticText(this, wxID_ANY, "Saturday:");
        lblSaturdaySchedule = new wxStaticText(this, wxID_ANY, "");

        ///////////////////////////////////////////////////////////////////////////

        wxGridSizer* gridSizer = new wxGridSizer(7, 2, wxSize{10, 10});

        wxSizerFlags flagsLblLeft = wxSizerFlags().CenterVertical().Left();
        wxSizerFlags flagsLblRight = wxSizerFlags().CenterVertical().Right();

        gridSizer->Add(lblSunday, flagsLblRight);
        gridSizer->Add(lblSundaySchedule, flagsLblLeft);

        gridSizer->Add(lblMonday, flagsLblRight);
        gridSizer->Add(lblMondaySchedule, flagsLblLeft);

        gridSizer->Add(lblTuesday, flagsLblRight);
        gridSizer->Add(lblTuesdaySchedule, flagsLblLeft);

        gridSizer->Add(lblWednesday, flagsLblRight);
        gridSizer->Add(lblWednesdaySchedule, flagsLblLeft);

        gridSizer->Add(lblThursday, flagsLblRight);
        gridSizer->Add(lblThursdaySchedule, flagsLblLeft);

        gridSizer->Add(lblFriday, flagsLblRight);
        gridSizer->Add(lblFridaySchedule, flagsLblLeft);

        gridSizer->Add(lblSaturday, flagsLblRight);
        gridSizer->Add(lblSaturdaySchedule, flagsLblLeft);

        ///////////////////////////////////////////////////////////////////////////

        boxSizer = new wxBoxSizer(wxVERTICAL);

        wxBoxSizer* szr = new wxBoxSizer(wxVERTICAL);

        wxSizerFlags flags = wxSizerFlags().Border(wxALL, 10).Expand();

        szr->Add(gridSizer, flags);
        szr->Add(boxSizer, flags);

        wxSizer* szrButton = CreateButtonSizer(wxOK);
        if (szrButton)
        {
            szr->Add(szrButton, wxSizerFlags().Center());
        }

        SetSizerAndFit(szr);
    }

    void ExchangeScheduleDialog::UpdateStuff(Api* api)
    {
        boxSizer->Clear();

        try
        {
            std::shared_ptr<ExchangeScheduleResponse> schedule = api->GetExchangeSchedule();

            lblSundaySchedule->SetLabel(wxString::Format(L"%s—%s ET", schedule->schedule->standard_hours->sunday->open_time->c_str(), schedule->schedule->standard_hours->sunday->close_time->c_str()));
            lblMondaySchedule->SetLabel(wxString::Format(L"%s—%s ET", schedule->schedule->standard_hours->monday->open_time->c_str(), schedule->schedule->standard_hours->monday->close_time->c_str()));
            lblTuesdaySchedule->SetLabel(wxString::Format(L"%s—%s ET", schedule->schedule->standard_hours->tuesday->open_time->c_str(), schedule->schedule->standard_hours->tuesday->close_time->c_str()));
            lblWednesdaySchedule->SetLabel(wxString::Format(L"%s—%s ET", schedule->schedule->standard_hours->wednesday->open_time->c_str(), schedule->schedule->standard_hours->wednesday->close_time->c_str()));
            lblThursdaySchedule->SetLabel(wxString::Format(L"%s—%s ET", schedule->schedule->standard_hours->thursday->open_time->c_str(), schedule->schedule->standard_hours->thursday->close_time->c_str()));
            lblFridaySchedule->SetLabel(wxString::Format(L"%s—%s ET", schedule->schedule->standard_hours->friday->open_time->c_str(), schedule->schedule->standard_hours->friday->close_time->c_str()));
            lblSaturdaySchedule->SetLabel(wxString::Format(L"%s—%s ET", schedule->schedule->standard_hours->saturday->open_time->c_str(), schedule->schedule->standard_hours->saturday->close_time->c_str()));

            if (schedule->schedule->maintenance_windows->empty())
            {
                boxSizer->Add(new wxStaticText(this, wxID_ANY, "No scheduled maintenance closures."), wxSizerFlags().Center());
            }
            else
            {
                boxSizer->Add(new wxStaticText(this, wxID_ANY, "Scheduled maintenance closures:"), wxSizerFlags().Center());

                wxGridSizer* gridSizer = new wxGridSizer(0, 2, wxSize{10, 10});

                wxSizerFlags flagsLblCenter = wxSizerFlags().CenterVertical().Center();
                wxSizerFlags flagsLblLeft = wxSizerFlags().CenterVertical().Left();

                gridSizer->Add(new wxStaticText(this, wxID_ANY, "Start"), flagsLblCenter);
                gridSizer->Add(new wxStaticText(this, wxID_ANY, "End"), flagsLblCenter);

                for (auto maint : *schedule->schedule->maintenance_windows)
                {
                    gridSizer->Add(new wxStaticText(this, wxID_ANY, maint->start_datetime->c_str()), flagsLblLeft);
                    gridSizer->Add(new wxStaticText(this, wxID_ANY, maint->end_datetime->c_str()), flagsLblLeft);
                }

                boxSizer->Add(gridSizer);
            }
        }
        catch (const std::exception &e)
        {
            wxCommandEvent* evt = new wxCommandEvent(EVT_API_ERROR);
            evt->SetEventObject(this);
            evt->SetString("Exchange schedule failed!");
            QueueEvent(evt);
        }
    }
}
