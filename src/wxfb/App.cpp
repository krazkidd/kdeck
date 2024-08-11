///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-33-g6494dcef)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "App.h"

///////////////////////////////////////////////////////////////////////////
using namespace kdeck::wxfb;

MainFrame::MainFrame()
{
}

MainFrame::MainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style )
{
	this->Create( parent, id, title, pos, size, style );
}

bool MainFrame::Create( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style )
{
	if ( !wxFrame::Create( parent, id, title, pos, size, style ) )
	{
		return false;
	}

	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* vszrRoot;
	vszrRoot = new wxBoxSizer( wxVERTICAL );

	pnlRoot = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* vszrContent;
	vszrContent = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* hszrPortfolioInfo;
	hszrPortfolioInfo = new wxBoxSizer( wxHORIZONTAL );


	hszrPortfolioInfo->Add( 0, 0, 1, wxEXPAND, 5 );

	lblBalance = new wxStaticText( pnlRoot, wxID_ANY, _("Balance"), wxDefaultPosition, wxDefaultSize, 0 );
	lblBalance->Wrap( -1 );
	hszrPortfolioInfo->Add( lblBalance, 0, wxALL, 5 );

	txtBalance = new wxTextCtrl( pnlRoot, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	hszrPortfolioInfo->Add( txtBalance, 0, wxALL, 5 );


	vszrContent->Add( hszrPortfolioInfo, 0, wxEXPAND, 5 );

	gridPositions = new wxGrid( pnlRoot, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );

	// Grid
	gridPositions->CreateGrid( 0, 6 );
	gridPositions->EnableEditing( true );
	gridPositions->EnableGridLines( true );
	gridPositions->EnableDragGridSize( false );
	gridPositions->SetMargins( 0, 0 );

	// Columns
	gridPositions->EnableDragColMove( false );
	gridPositions->EnableDragColSize( true );
	gridPositions->SetColLabelValue( 0, _("Ticker") );
	gridPositions->SetColLabelValue( 1, _("Position") );
	gridPositions->SetColLabelValue( 2, _("Exposure") );
	gridPositions->SetColLabelValue( 3, _("Realized P/L") );
	gridPositions->SetColLabelValue( 4, _("Total Traded") );
	gridPositions->SetColLabelValue( 5, _("Resting Orders") );
	gridPositions->SetColLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Rows
	gridPositions->EnableDragRowSize( true );
	gridPositions->SetRowLabelAlignment( wxALIGN_CENTER, wxALIGN_CENTER );

	// Label Appearance

	// Cell Defaults
	gridPositions->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	vszrContent->Add( gridPositions, 1, wxALL|wxEXPAND, 5 );


	pnlRoot->SetSizer( vszrContent );
	pnlRoot->Layout();
	vszrContent->Fit( pnlRoot );
	vszrRoot->Add( pnlRoot, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( vszrRoot );
	this->Layout();
	mnuBar = new wxMenuBar( 0 );
	mnuFile = new wxMenu();
	mnuLogin = new wxMenuItem( mnuFile, ID_Login, wxString( _("Login...") ) , _("Login"), wxITEM_NORMAL );
	mnuFile->Append( mnuLogin );

	mnuLogout = new wxMenuItem( mnuFile, ID_Logout, wxString( _("Logout...") ) , _("Logout"), wxITEM_NORMAL );
	mnuFile->Append( mnuLogout );
	mnuLogout->Enable( false );

	mnuFile->AppendSeparator();

	wxMenuItem* mnuExit;
	mnuExit = new wxMenuItem( mnuFile, wxID_EXIT, wxString( wxEmptyString ) , wxEmptyString, wxITEM_NORMAL );
	mnuFile->Append( mnuExit );

	mnuBar->Append( mnuFile, _("&File") );

	mnuExchange = new wxMenu();
	wxMenuItem* mnuItemExchangeAnnouncements;
	mnuItemExchangeAnnouncements = new wxMenuItem( mnuExchange, ID_Exchange_Announcements, wxString( _("Announcements") ) , _("Announcements"), wxITEM_NORMAL );
	mnuExchange->Append( mnuItemExchangeAnnouncements );

	wxMenuItem* mnuItemExchangeSchedule;
	mnuItemExchangeSchedule = new wxMenuItem( mnuExchange, ID_Exchange_Schedule, wxString( _("Schedule") ) , _("Schedule"), wxITEM_NORMAL );
	mnuExchange->Append( mnuItemExchangeSchedule );

	wxMenuItem* mnuItemExchangeStatus;
	mnuItemExchangeStatus = new wxMenuItem( mnuExchange, ID_Exchange_Status, wxString( _("Status") ) , _("Status"), wxITEM_NORMAL );
	mnuExchange->Append( mnuItemExchangeStatus );

	mnuBar->Append( mnuExchange, _("&Exchange") );

	mnuView = new wxMenu();
	mnuShowClosedPositions = new wxMenuItem( mnuView, ID_View_ShowClosedPositions, wxString( _("Show Closed Positions") ) , _("Show Closed Positions"), wxITEM_CHECK );
	mnuView->Append( mnuShowClosedPositions );
	mnuShowClosedPositions->Enable( false );

	mnuBar->Append( mnuView, _("&View") );

	mnuHelp = new wxMenu();
	wxMenuItem* mnuAbout;
	mnuAbout = new wxMenuItem( mnuHelp, wxID_ABOUT, wxString( wxEmptyString ) , wxEmptyString, wxITEM_NORMAL );
	mnuHelp->Append( mnuAbout );

	mnuBar->Append( mnuHelp, _("&Help") );

	this->SetMenuBar( mnuBar );

	statusBar = this->CreateStatusBar( 3, wxSTB_SIZEGRIP, wxID_ANY );

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainFrame::OnClose ) );
	this->Connect( wxEVT_SHOW, wxShowEventHandler( MainFrame::OnShow ) );
	mnuFile->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnMenuItemSelected ), this, mnuLogin->GetId());
	mnuFile->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnMenuItemSelected ), this, mnuLogout->GetId());
	mnuFile->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnMenuItemSelected ), this, mnuExit->GetId());
	mnuExchange->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnMenuItemSelected ), this, mnuItemExchangeAnnouncements->GetId());
	mnuExchange->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnMenuItemSelected ), this, mnuItemExchangeSchedule->GetId());
	mnuExchange->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnMenuItemSelected ), this, mnuItemExchangeStatus->GetId());
	mnuView->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnMenuItemSelected ), this, mnuShowClosedPositions->GetId());
	mnuHelp->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainFrame::OnMenuItemSelected ), this, mnuAbout->GetId());

	return true;
}

MainFrame::~MainFrame()
{
}
