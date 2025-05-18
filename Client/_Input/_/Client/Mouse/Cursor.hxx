#pragma once

namespace NOppression::NClient::NMouse
{
    struct SCursor
    {
        bool FModification;
        std::shared_ptr<SAbsolute> FAbsolute;
        std::shared_ptr<SRelative> FRelative;

        SCursor();
        SCursor* IPreupdate();
        SCursor* IPostupdate(SDL_MouseMotionEvent const& AMotion);
        ~SCursor();
    };
}