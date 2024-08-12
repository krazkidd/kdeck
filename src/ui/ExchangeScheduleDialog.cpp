#include <wx/string.h>
#include <wx/wx.h>

#include "App.h" // wxfb

#include "api/Api.hpp"
#include "ui/ExchangeScheduleDialog.hpp"
#include "ui/event.hpp"

namespace kdeck
{
    class ExchangeScheduleResponse;

    void ExchangeScheduleDialog::UpdateStuff(Api* api)
    {
        gszrMaintenanceSchedule->Clear(true);

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

            bool hasMaintenanceScheduled = !schedule->schedule->maintenance_windows->empty();

            lblScheduledMaintenance->Show(hasMaintenanceScheduled);
            gszrMaintenanceScheduleColumns->Show(hasMaintenanceScheduled);
            gszrMaintenanceSchedule->Show(hasMaintenanceScheduled);

            wxSizerFlags flagsLblLeft = wxSizerFlags().CenterVertical().Left();
            for (auto maint : *schedule->schedule->maintenance_windows)
            {
                gszrMaintenanceSchedule->Add(new wxStaticText(this, wxID_ANY, maint->start_datetime->c_str()), flagsLblLeft);
                gszrMaintenanceSchedule->Add(new wxStaticText(this, wxID_ANY, maint->end_datetime->c_str()), flagsLblLeft);
            }

            lblNoScheduledMaintenance->Show(!hasMaintenanceScheduled);
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
