#include "ui/App.h"
#include "ui/MainFrame.h"

bool App::OnInit()
{
    MainFrame *frame = new MainFrame();
    frame->Show();
    return true;
}
