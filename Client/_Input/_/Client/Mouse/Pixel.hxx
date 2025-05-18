#pragma once

namespace NOppression::NClient::NMouse
{
    struct SPixel
    {
        bool FModification;
        std::int64_t FX;
        std::int64_t FY;

        SPixel();
        SPixel* IPreupdate();
        SPixel* IPostupdate(std::int64_t const& AX , std::int64_t const& AY);
        ~SPixel();
    };
}