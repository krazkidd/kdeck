#include <string>

#include <wx/wx.h>

#include "ui/PortfolioPanel.h"
#include "ui/MainFrame.h"
#include "api/Api.h"

// constructor ////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

PortfolioPanel::PortfolioPanel(wxWindow* parent)
    : wxPanel(parent, wxID_ANY)
{
    Setup();
    Update();
}

// init ///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void PortfolioPanel::Setup()
{
    wxStaticText* lblBalance = new wxStaticText(this, wxID_ANY, "Balance:");
    lblBalanceAmount = new wxStaticText(this, wxID_ANY, "");

    pnlPositions = new wxPanel(this, wxID_ANY);

    wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);

    wxSizerFlags flagsLbl = wxSizerFlags().Border(wxALL, 25).Left();
    //wxSizerFlags flagsInput = wxSizerFlags().Border(wxALL, 25).Expand();

    boxSizer->Add(lblBalance, flagsLbl);
    boxSizer->Add(lblBalanceAmount, flagsLbl);
    boxSizer->Add(pnlPositions, flagsLbl);

    SetSizer(boxSizer);
}

void PortfolioPanel::Update()
{
    try
    {
        lblBalanceAmount->SetLabelText(std::to_string(Api::GetBalance()));

        pnlPositions->DestroyChildren();

        for (const PortfolioPositionsResponse::MarketPosition &position : Api::GetPositions())
        {
            new wxStaticText(pnlPositions, wxID_ANY, position.ticker);
        }

        wxLogStatus("Portfolio update succeeded!");
    }
    catch (std::logic_error &e)
    {
        wxLogError(e.what());

        wxLogStatus("Portfolio update failed!");
    }
    catch (std::runtime_error &e)
    {
        wxLogError("Unknown error.");
        wxLogDebug(e.what());

        wxLogStatus("Portfolio update failed!");
    }
}
