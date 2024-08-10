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
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/grid.h>
#include <wx/panel.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/statusbr.h>
#include <wx/frame.h>

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
				wxStaticText* lblBalance;
				wxTextCtrl* txtBalance;
				wxGrid* gridPositions;
				wxMenuBar* mnuBar;
				wxMenu* mnuFile;
				wxMenu* mnuExchange;
				wxMenu* mnuView;
				wxMenu* mnuHelp;
				wxStatusBar* statusBar;

				// Virtual event handlers, override them in your derived class
				virtual void OnMenuItemSelected( wxCommandEvent& event ) { event.Skip(); }


			public:

				MainFrame();
				MainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("kdeck"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 800,600 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
				bool Create( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("kdeck"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 800,600 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

				~MainFrame();

		};

	} // namespace wxfb
} // namespace kdeck

