#include "ui/App.hpp"
#include "ui/MainFrame.hpp"

namespace kdeck
{
    bool App::OnInit()
    {
        MainFrame *frame = new MainFrame();
        frame->Show();
        return true;
    }
}
