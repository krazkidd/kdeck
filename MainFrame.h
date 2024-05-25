#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <wx/wx.h>
#include <curlpp/cURLpp.hpp>

class MainFrame : public wxFrame
{
public:
    MainFrame();

private:
    // handles global cURLpp::initialize()/terminate()
    cURLpp::Cleanup cURLpp();

    // init
    void AddMenuBar();
    void AddLoginPanel();

    // event handlers
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};

#endif