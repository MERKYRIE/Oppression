#pragma once

namespace NOppression::NClient::NMouse
{
    struct SWheel
    {
        bool FModification;
        double FState;

        SWheel();
        SWheel* IPreupdate();
        SWheel* IPostupdate(SDL_MouseWheelEvent const& AWheel);
        ~SWheel();
    };
}