#pragma once

namespace NOppression::NClient
{
    inline struct STime
    {
        double FLast;
        double FAbsolute;
        double FRelative;

        void IUpdate();
    }
    GTime;
}