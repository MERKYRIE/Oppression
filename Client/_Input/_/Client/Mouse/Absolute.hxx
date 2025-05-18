#pragma once

namespace NOppression::NClient::NMouse
{
    struct SAbsolute
    {
        bool FModification;
        std::shared_ptr<SPixel> FPixel;
        std::shared_ptr<SRectangle> FRectangle;
        std::shared_ptr<SSquare> FSquare;

        SAbsolute();
        SAbsolute* IPreupdate();
        SAbsolute* IPostupdate(SDL_MouseMotionEvent const& AMotion);
        ~SAbsolute();
    };
}