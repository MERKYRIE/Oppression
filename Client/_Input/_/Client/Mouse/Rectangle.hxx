#pragma once

namespace NOppression::NClient::NMouse
{
    struct SRectangle
    {
        bool FModification;
        double FX;
        double FY;

        SRectangle();
        SRectangle* IPreupdate();
        SRectangle* IPostupdate(std::int64_t const& AX , std::int64_t const& AY);
        ~SRectangle();
    };
}