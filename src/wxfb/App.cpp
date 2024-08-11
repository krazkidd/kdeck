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

	pnlPortfolio = new PortfolioPanel(pnlRoot);
	vszrContent->Add( pnlPortfolio, 1, wxALL|wxEXPAND, 5 );


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

LoginDialog::LoginDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* vszrContent;
	vszrContent = new wxBoxSizer( wxVERTICAL );

	wxGridSizer* gridInputs;
	gridInputs = new wxGridSizer( 0, 2, 0, 0 );

	wxStaticText* lblEmail;
	lblEmail = new wxStaticText( this, wxID_ANY, _("Email"), wxDefaultPosition, wxDefaultSize, 0 );
	lblEmail->Wrap( -1 );
	gridInputs->Add( lblEmail, 0, wxALIGN_RIGHT|wxALL, 5 );

	txtEmail = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gridInputs->Add( txtEmail, 0, wxALL|wxEXPAND, 5 );

	wxStaticText* lblPassword;
	lblPassword = new wxStaticText( this, wxID_ANY, _("Password"), wxDefaultPosition, wxDefaultSize, 0 );
	lblPassword->Wrap( -1 );
	gridInputs->Add( lblPassword, 0, wxALIGN_RIGHT|wxALL, 5 );

	txtPassword = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD );
	gridInputs->Add( txtPassword, 0, wxALL|wxEXPAND, 5 );


	vszrContent->Add( gridInputs, 1, wxEXPAND, 5 );

	chkRememberMe = new wxCheckBox( this, wxID_ANY, _("Remember me"), wxDefaultPosition, wxDefaultSize, 0 );
	vszrContent->Add( chkRememberMe, 0, wxALL, 5 );

	wxStdDialogButtonSizer* szrStandardButtons;
	wxButton* szrStandardButtonsOK;
	wxButton* szrStandardButtonsCancel;
	szrStandardButtons = new wxStdDialogButtonSizer();
	szrStandardButtonsOK = new wxButton( this, wxID_OK );
	szrStandardButtons->AddButton( szrStandardButtonsOK );
	szrStandardButtonsCancel = new wxButton( this, wxID_CANCEL );
	szrStandardButtons->AddButton( szrStandardButtonsCancel );
	szrStandardButtons->Realize();

	vszrContent->Add( szrStandardButtons, 0, wxEXPAND, 5 );


	this->SetSizer( vszrContent );
	this->Layout();
	vszrContent->Fit( this );

	this->Centre( wxBOTH );
}

LoginDialog::~LoginDialog()
{
}

ExchangeAnnouncementsDialog::ExchangeAnnouncementsDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* vszrContent;
	vszrContent = new wxBoxSizer( wxVERTICAL );

	fgszrAnnouncements = new wxFlexGridSizer( 1, 4, 0, 0 );
	fgszrAnnouncements->AddGrowableCol( 3 );
	fgszrAnnouncements->SetFlexibleDirection( wxBOTH );
	fgszrAnnouncements->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );


	vszrContent->Add( fgszrAnnouncements, 1, wxEXPAND, 5 );

	lblNoAnnouncements = new wxStaticText( this, wxID_ANY, _("There are no announcements."), wxDefaultPosition, wxDefaultSize, 0 );
	lblNoAnnouncements->Wrap( -1 );
	vszrContent->Add( lblNoAnnouncements, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

	wxStdDialogButtonSizer* szrStandardButtons;
	wxButton* szrStandardButtonsOK;
	szrStandardButtons = new wxStdDialogButtonSizer();
	szrStandardButtonsOK = new wxButton( this, wxID_OK );
	szrStandardButtons->AddButton( szrStandardButtonsOK );
	szrStandardButtons->Realize();

	vszrContent->Add( szrStandardButtons, 0, wxEXPAND, 5 );


	this->SetSizer( vszrContent );
	this->Layout();
	vszrContent->Fit( this );

	this->Centre( wxBOTH );
}

ExchangeAnnouncementsDialog::~ExchangeAnnouncementsDialog()
{
}

ExchangeScheduleDialog::ExchangeScheduleDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* vszrContent;
	vszrContent = new wxBoxSizer( wxVERTICAL );

	wxGridSizer* gszrSchedule;
	gszrSchedule = new wxGridSizer( 0, 2, 0, 0 );

	wxStaticText* lblSunday;
	lblSunday = new wxStaticText( this, wxID_ANY, _("Sunday"), wxDefaultPosition, wxDefaultSize, 0 );
	lblSunday->Wrap( -1 );
	gszrSchedule->Add( lblSunday, 0, wxALIGN_RIGHT|wxALL, 5 );

	lblSundaySchedule = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	lblSundaySchedule->Wrap( -1 );
	gszrSchedule->Add( lblSundaySchedule, 0, wxALIGN_LEFT|wxALL, 5 );

	wxStaticText* lblMonday;
	lblMonday = new wxStaticText( this, wxID_ANY, _("Monday"), wxDefaultPosition, wxDefaultSize, 0 );
	lblMonday->Wrap( -1 );
	gszrSchedule->Add( lblMonday, 0, wxALIGN_RIGHT|wxALL, 5 );

	lblMondaySchedule = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	lblMondaySchedule->Wrap( -1 );
	gszrSchedule->Add( lblMondaySchedule, 0, wxALL, 5 );

	wxStaticText* lblTuesday;
	lblTuesday = new wxStaticText( this, wxID_ANY, _("Tuesday"), wxDefaultPosition, wxDefaultSize, 0 );
	lblTuesday->Wrap( -1 );
	gszrSchedule->Add( lblTuesday, 0, wxALIGN_RIGHT|wxALL, 5 );

	lblTuesdaySchedule = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	lblTuesdaySchedule->Wrap( -1 );
	gszrSchedule->Add( lblTuesdaySchedule, 0, wxALL, 5 );

	wxStaticText* lblWednesday;
	lblWednesday = new wxStaticText( this, wxID_ANY, _("Wednesday"), wxDefaultPosition, wxDefaultSize, 0 );
	lblWednesday->Wrap( -1 );
	gszrSchedule->Add( lblWednesday, 0, wxALIGN_RIGHT|wxALL, 5 );

	lblWednesdaySchedule = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	lblWednesdaySchedule->Wrap( -1 );
	gszrSchedule->Add( lblWednesdaySchedule, 0, wxALL, 5 );

	wxStaticText* lblThursday;
	lblThursday = new wxStaticText( this, wxID_ANY, _("Thursday"), wxDefaultPosition, wxDefaultSize, 0 );
	lblThursday->Wrap( -1 );
	gszrSchedule->Add( lblThursday, 0, wxALIGN_RIGHT|wxALL, 5 );

	lblThursdaySchedule = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	lblThursdaySchedule->Wrap( -1 );
	gszrSchedule->Add( lblThursdaySchedule, 0, wxALL, 5 );

	wxStaticText* lblFriday;
	lblFriday = new wxStaticText( this, wxID_ANY, _("Friday"), wxDefaultPosition, wxDefaultSize, 0 );
	lblFriday->Wrap( -1 );
	gszrSchedule->Add( lblFriday, 0, wxALIGN_RIGHT|wxALL, 5 );

	lblFridaySchedule = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	lblFridaySchedule->Wrap( -1 );
	gszrSchedule->Add( lblFridaySchedule, 0, wxALL, 5 );

	wxStaticText* lblSaturday;
	lblSaturday = new wxStaticText( this, wxID_ANY, _("Saturday"), wxDefaultPosition, wxDefaultSize, 0 );
	lblSaturday->Wrap( -1 );
	gszrSchedule->Add( lblSaturday, 0, wxALIGN_RIGHT|wxALL, 5 );

	lblSaturdaySchedule = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	lblSaturdaySchedule->Wrap( -1 );
	gszrSchedule->Add( lblSaturdaySchedule, 0, wxALL, 5 );


	vszrContent->Add( gszrSchedule, 1, wxEXPAND, 5 );

	lblScheduledMaintenance = new wxStaticText( this, wxID_ANY, _("Scheduled Maintenance Closures"), wxDefaultPosition, wxDefaultSize, 0 );
	lblScheduledMaintenance->Wrap( -1 );
	vszrContent->Add( lblScheduledMaintenance, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

	gszrMaintenanceScheduleColumns = new wxGridSizer( 0, 2, 0, 0 );

	wxStaticText* lblStart;
	lblStart = new wxStaticText( this, wxID_ANY, _("Start"), wxDefaultPosition, wxDefaultSize, 0 );
	lblStart->Wrap( -1 );
	gszrMaintenanceScheduleColumns->Add( lblStart, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

	wxStaticText* m_staticText118;
	m_staticText118 = new wxStaticText( this, wxID_ANY, _("End"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText118->Wrap( -1 );
	gszrMaintenanceScheduleColumns->Add( m_staticText118, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxLEFT, 5 );


	vszrContent->Add( gszrMaintenanceScheduleColumns, 0, wxEXPAND, 5 );

	gszrMaintenanceSchedule = new wxGridSizer( 0, 2, 0, 0 );


	vszrContent->Add( gszrMaintenanceSchedule, 1, wxEXPAND, 5 );

	lblNoScheduledMaintenance = new wxStaticText( this, wxID_ANY, _("There are no scheduled maintenance closures."), wxDefaultPosition, wxDefaultSize, 0 );
	lblNoScheduledMaintenance->Wrap( -1 );
	vszrContent->Add( lblNoScheduledMaintenance, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );

	wxStdDialogButtonSizer* szrStandardButtons;
	wxButton* szrStandardButtonsOK;
	szrStandardButtons = new wxStdDialogButtonSizer();
	szrStandardButtonsOK = new wxButton( this, wxID_OK );
	szrStandardButtons->AddButton( szrStandardButtonsOK );
	szrStandardButtons->Realize();

	vszrContent->Add( szrStandardButtons, 0, wxEXPAND, 5 );


	this->SetSizer( vszrContent );
	this->Layout();
	vszrContent->Fit( this );

	this->Centre( wxBOTH );
}

ExchangeScheduleDialog::~ExchangeScheduleDialog()
{
}

ExchangeStatusDialog::ExchangeStatusDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* vszrContent;
	vszrContent = new wxBoxSizer( wxVERTICAL );

	wxGridSizer* gszrStatus;
	gszrStatus = new wxGridSizer( 0, 2, 0, 0 );

	wxStaticText* lblExchange;
	lblExchange = new wxStaticText( this, wxID_ANY, _("Exchange"), wxDefaultPosition, wxDefaultSize, 0 );
	lblExchange->Wrap( -1 );
	gszrStatus->Add( lblExchange, 0, wxALIGN_RIGHT|wxALL, 5 );

	lblExchangeStatus = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	lblExchangeStatus->Wrap( -1 );
	gszrStatus->Add( lblExchangeStatus, 0, wxALL, 5 );

	wxStaticText* lblTrading;
	lblTrading = new wxStaticText( this, wxID_ANY, _("Trading"), wxDefaultPosition, wxDefaultSize, 0 );
	lblTrading->Wrap( -1 );
	gszrStatus->Add( lblTrading, 0, wxALIGN_RIGHT|wxALL, 5 );

	lblTradingStatus = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	lblTradingStatus->Wrap( -1 );
	gszrStatus->Add( lblTradingStatus, 0, wxALL, 5 );


	vszrContent->Add( gszrStatus, 1, wxEXPAND, 5 );

	wxStdDialogButtonSizer* szrStandardButtons;
	wxButton* szrStandardButtonsOK;
	szrStandardButtons = new wxStdDialogButtonSizer();
	szrStandardButtonsOK = new wxButton( this, wxID_OK );
	szrStandardButtons->AddButton( szrStandardButtonsOK );
	szrStandardButtons->Realize();

	vszrContent->Add( szrStandardButtons, 0, wxEXPAND, 5 );


	this->SetSizer( vszrContent );
	this->Layout();
	vszrContent->Fit( this );

	this->Centre( wxBOTH );
}

ExchangeStatusDialog::~ExchangeStatusDialog()
{
}
