#ifndef APP_HPP
#define APP_HPP

#include <wx/wx.h>

namespace kdeck
{
    class App : public wxApp
    {
    public:
        bool OnInit() override;
    };
}

#endif
