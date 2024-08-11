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

	wxBoxSizer* vszrRoot;
	vszrRoot = new wxBoxSizer( wxVERTICAL );

	pnlRoot = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* vszrContent;
	vszrContent = new wxBoxSizer( wxVERTICAL );

	wxGridSizer* gridInputs;
	gridInputs = new wxGridSizer( 0, 2, 0, 0 );

	wxStaticText* lblEmail;
	lblEmail = new wxStaticText( pnlRoot, wxID_ANY, _("Email"), wxDefaultPosition, wxDefaultSize, 0 );
	lblEmail->Wrap( -1 );
	gridInputs->Add( lblEmail, 0, wxALIGN_RIGHT|wxALL, 5 );

	txtEmail = new wxTextCtrl( pnlRoot, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	gridInputs->Add( txtEmail, 0, wxALL|wxEXPAND, 5 );

	wxStaticText* lblPassword;
	lblPassword = new wxStaticText( pnlRoot, wxID_ANY, _("Password"), wxDefaultPosition, wxDefaultSize, 0 );
	lblPassword->Wrap( -1 );
	gridInputs->Add( lblPassword, 0, wxALIGN_RIGHT|wxALL, 5 );

	txtPassword = new wxTextCtrl( pnlRoot, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD );
	gridInputs->Add( txtPassword, 0, wxALL|wxEXPAND, 5 );


	vszrContent->Add( gridInputs, 1, wxEXPAND, 5 );

	chkRememberMe = new wxCheckBox( pnlRoot, wxID_ANY, _("Remember me"), wxDefaultPosition, wxDefaultSize, 0 );
	vszrContent->Add( chkRememberMe, 0, wxALL, 5 );

	wxStdDialogButtonSizer* szrStandardButtons;
	wxButton* szrStandardButtonsOK;
	wxButton* szrStandardButtonsCancel;
	szrStandardButtons = new wxStdDialogButtonSizer();
	szrStandardButtonsOK = new wxButton( pnlRoot, wxID_OK );
	szrStandardButtons->AddButton( szrStandardButtonsOK );
	szrStandardButtonsCancel = new wxButton( pnlRoot, wxID_CANCEL );
	szrStandardButtons->AddButton( szrStandardButtonsCancel );
	szrStandardButtons->Realize();

	vszrContent->Add( szrStandardButtons, 0, wxEXPAND, 5 );


	pnlRoot->SetSizer( vszrContent );
	pnlRoot->Layout();
	vszrContent->Fit( pnlRoot );
	vszrRoot->Add( pnlRoot, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( vszrRoot );
	this->Layout();
	vszrRoot->Fit( this );

	this->Centre( wxBOTH );
}

LoginDialog::~LoginDialog()
{
}
