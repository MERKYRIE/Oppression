#pragma once

namespace NOppression::NServer::NSpace
{
    struct SOrder
    {
        std::int64_t FFromX;
        std::int64_t FFromY;
        std::int64_t FToX;
        std::int64_t FToY;
        double FTimer;
        double FDuration;
        
        SOrder(std::int64_t const& AFromX , std::int64_t const& AFromY , std::int64_t const& AToX , std::int64_t const& AToY , double const& ADuration);
        void IUpdate();
        bool ICompleted();
    };
}