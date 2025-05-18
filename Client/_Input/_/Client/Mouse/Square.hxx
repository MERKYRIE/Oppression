#pragma once

namespace NOppression::NClient::NMouse
{
    struct SSquare
    {
        bool FModification;
        double FX;
        double FY;

        SSquare();
        SSquare* IPreupdate();
        SSquare* IPostupdate(std::int64_t const& AX , std::int64_t const& AY);
        ~SSquare();
    };
}