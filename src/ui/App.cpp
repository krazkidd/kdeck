#include "oatpp/core/base/Environment.hpp"

#include "ui/App.hpp"
#include "ui/MainFrame.hpp"

namespace kdeck
{
    bool App::OnInit()
    {
        oatpp::base::Environment::init();

        MainFrame *frame = new MainFrame();
        frame->Show();

        return true;
    }

    int App::OnExit()
    {
        oatpp::base::Environment::destroy();

        return 0;
    }
}
