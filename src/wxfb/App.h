///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-33-g6494dcef)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include "ui/PortfolioPanel.hpp"
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/button.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

namespace kdeck
{
	namespace wxfb
	{
		///////////////////////////////////////////////////////////////////////////////
		/// Class MainFrame
		///////////////////////////////////////////////////////////////////////////////
		class MainFrame : public wxFrame
		{
			private:

			protected:
				enum
				{
					ID_Login = 6000,
					ID_Logout,
					ID_Exchange_Announcements,
					ID_Exchange_Schedule,
					ID_Exchange_Status,
					ID_View_ShowClosedPositions,
				};

				wxPanel* pnlRoot;
				kdeck::PortfolioPanel* pnlPortfolio;
				wxMenuBar* mnuBar;
				wxMenu* mnuFile;
				wxMenuItem* mnuLogin;
				wxMenuItem* mnuLogout;
				wxMenu* mnuExchange;
				wxMenu* mnuView;
				wxMenuItem* mnuShowClosedPositions;
				wxMenu* mnuHelp;
				wxStatusBar* statusBar;

				// Virtual event handlers, override them in your derived class
				virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
				virtual void OnShow( wxShowEvent& event ) { event.Skip(); }
				virtual void OnMenuItemSelected( wxCommandEvent& event ) { event.Skip(); }


			public:

				MainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 800,600 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

				~MainFrame();

		};

		///////////////////////////////////////////////////////////////////////////////
		/// Class LoginDialog
		///////////////////////////////////////////////////////////////////////////////
		class LoginDialog : public wxDialog
		{
			private:

			protected:
				wxTextCtrl* txtEmail;
				wxTextCtrl* txtPassword;
				wxCheckBox* chkRememberMe;

			public:

				LoginDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Login"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );

				~LoginDialog();

		};

		///////////////////////////////////////////////////////////////////////////////
		/// Class ExchangeAnnouncementsDialog
		///////////////////////////////////////////////////////////////////////////////
		class ExchangeAnnouncementsDialog : public wxDialog
		{
			private:

			protected:
				wxFlexGridSizer* fgszrAnnouncements;
				wxStaticText* lblNoAnnouncements;

			public:

				ExchangeAnnouncementsDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Exchange Announcements"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );

				~ExchangeAnnouncementsDialog();

		};

		///////////////////////////////////////////////////////////////////////////////
		/// Class ExchangeScheduleDialog
		///////////////////////////////////////////////////////////////////////////////
		class ExchangeScheduleDialog : public wxDialog
		{
			private:

			protected:
				wxStaticText* lblSundaySchedule;
				wxStaticText* lblMondaySchedule;
				wxStaticText* lblTuesdaySchedule;
				wxStaticText* lblWednesdaySchedule;
				wxStaticText* lblThursdaySchedule;
				wxStaticText* lblFridaySchedule;
				wxStaticText* lblSaturdaySchedule;
				wxStaticText* lblScheduledMaintenance;
				wxGridSizer* gszrMaintenanceScheduleColumns;
				wxGridSizer* gszrMaintenanceSchedule;
				wxStaticText* lblNoScheduledMaintenance;

			public:

				ExchangeScheduleDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Exchange Schedule"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );

				~ExchangeScheduleDialog();

		};

		///////////////////////////////////////////////////////////////////////////////
		/// Class ExchangeStatusDialog
		///////////////////////////////////////////////////////////////////////////////
		class ExchangeStatusDialog : public wxDialog
		{
			private:

			protected:
				wxStaticText* lblExchangeStatus;
				wxStaticText* lblTradingStatus;

			public:

				ExchangeStatusDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Exchange Status"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );

				~ExchangeStatusDialog();

		};

	} // namespace wxfb
} // namespace kdeck

