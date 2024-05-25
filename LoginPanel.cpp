#include <sstream>
#include <string>

#include <fmt/core.h>
#include <wx/wx.h>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>
#include <curlpp/Infos.hpp>

#include "config.h"
#include "LoginPanel.h"

// constructor ////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

LoginPanel::LoginPanel(wxWindow* parent)
    : wxPanel(parent, wxID_ANY)
{
    AddControls();
}

// init ///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void LoginPanel::AddControls()
{
    wxStaticText* lblName = new wxStaticText(this, wxID_ANY, "Email:");
    wxStaticText* lblPassword = new wxStaticText(this, wxID_ANY, "Password:");

    txtEmail = new wxTextCtrl(this, wxID_ANY);
    txtPassword = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);

    wxButton* btnLogin = new wxButton(this, wxID_ANY, "Login");
    btnLogin->Bind(wxEVT_BUTTON, &LoginPanel::OnLoginButtonClicked, this);

    wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);

    wxSizerFlags flagsLbl = wxSizerFlags().Border(wxALL, 25).Left();
    wxSizerFlags flagsInput = wxSizerFlags().Border(wxALL, 25).Expand();

    boxSizer->Add(lblName, flagsLbl);
    boxSizer->Add(txtEmail, flagsInput);
    boxSizer->Add(lblPassword, flagsLbl);
    boxSizer->Add(txtPassword, flagsInput);
    boxSizer->Add(btnLogin, flagsInput);

    SetSizer(boxSizer);
}

// API requests ///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//TODO move to own class
std::string LoginPanel::RequestLoginToken(std::string email, std::string password)
{
    if (email.empty())
    {
        wxLogMessage("Email not provided.");

        return std::string();
    }
    else if (password.empty())
    {
        wxLogMessage("Password not provided.");

        return std::string();
    }

    try
    {
        cURLpp::Easy req;
        std::stringstream res;

        req.setOpt(new cURLpp::Options::Post(true));
        req.setOpt(new cURLpp::Options::Url(std::string{kKalshiApiUrl}.append("/login")));
        //req.setOpt(new cURLpp::Options::Port(80));

        std::list<std::string> headers;
		headers.push_back("accept: application/json");
        headers.push_back("content-type: application/json");
        req.setOpt(new cURLpp::Options::HttpHeader(headers));

        req.setOpt(new cURLpp::Options::PostFields(fmt::format("{{\"email\":\"{0}\",\"password\":\"{1}\"}}", email, password)));

        req.setOpt(cURLpp::Options::WriteStream(&res));
        req.perform();

        if (cURLpp::infos::ResponseCode::get(req) == 200)
        {
            return res.str();
        }

        return std::string();
    }
    catch (cURLpp::RuntimeError &e)
    {
        wxLogDebug(e.what());
        wxLogError("Unknown CURL error.");
    }
    catch (cURLpp::LogicError &e)
    {
        wxLogDebug(e.what());
        wxLogError("Unknown CURL error.");
    }

    return std::string();
}


// event handlers /////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

void LoginPanel::OnLoginButtonClicked(wxCommandEvent& event)
{
    std::string loginToken = RequestLoginToken(txtEmail->GetValue().ToStdString(), txtPassword->GetValue().ToStdString());

    if (loginToken.empty()) {
        wxLogStatus("Login failed!");
    }
    else
    {
        wxLogStatus("Login succeeded!");
    }
}
