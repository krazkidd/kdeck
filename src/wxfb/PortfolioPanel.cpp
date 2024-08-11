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

	wxBoxSizer* hszrPortfolioInfo;
	hszrPortfolioInfo = new wxBoxSizer( wxHORIZONTAL );


	hszrPortfolioInfo->Add( 0, 0, 1, wxEXPAND, 5 );

	wxStaticText* lblBalance;
	lblBalance = new wxStaticText( this, wxID_ANY, _("Balance"), wxDefaultPosition, wxDefaultSize, 0 );
	lblBalance->Wrap( -1 );
	hszrPortfolioInfo->Add( lblBalance, 0, wxALL, 5 );

	lblBalanceAmount = new StaticCurrency(this);
	hszrPortfolioInfo->Add( lblBalanceAmount, 0, wxALL, 5 );


	vszrContent->Add( hszrPortfolioInfo, 0, wxEXPAND, 5 );

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
