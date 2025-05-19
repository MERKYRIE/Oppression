#pragma once

namespace NOppression::NClient::NVideo
{
    struct SImage
    {
        std::string FPath;
        SDL_Texture * FHandle;

        SImage(std::string const& APath);
        SImage(TTF_Font * const& AFont , std::string const& AString);
        double IWidth();
        double IHeight();
        double IMinimum();
        double IMaximum();
        ~SImage();
    };
}