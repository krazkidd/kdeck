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
#include "ui/BalancePanel.hpp"
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/scrolwin.h>
#include <wx/panel.h>

///////////////////////////////////////////////////////////////////////////

namespace kdeck
{
	namespace wxfb
	{
		///////////////////////////////////////////////////////////////////////////////
		/// Class PortfolioPanel
		///////////////////////////////////////////////////////////////////////////////
		class PortfolioPanel : public wxPanel
		{
			private:

			protected:
				BalancePanel* pnlBalance;
				wxScrolledWindow* pnlPositions;
				wxBoxSizer* vszrPositions;

			public:

				PortfolioPanel( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );

				~PortfolioPanel();

		};

	} // namespace wxfb
} // namespace kdeck

