///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-33-g6494dcef)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "PortfolioPanel.h"

///////////////////////////////////////////////////////////////////////////
using namespace kdeck::wxfb;

PortfolioPanel::PortfolioPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	wxBoxSizer* vszrContent;
	vszrContent = new wxBoxSizer( wxVERTICAL );

	pnlBalance = new BalancePanel(this);
	vszrContent->Add( pnlBalance, 0, wxALL, 5 );

	pnlPositions = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	pnlPositions->SetScrollRate( 5, 5 );
	vszrPositions = new wxBoxSizer( wxVERTICAL );


	pnlPositions->SetSizer( vszrPositions );
	pnlPositions->Layout();
	vszrPositions->Fit( pnlPositions );
	vszrContent->Add( pnlPositions, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( vszrContent );
	this->Layout();
}

PortfolioPanel::~PortfolioPanel()
{
}
