#pragma once

namespace NOppression::NServer
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