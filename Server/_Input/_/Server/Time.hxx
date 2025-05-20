#pragma once

namespace NOppression::NServer::NTime
{
    inline double FLast;
    inline double FAbsolute;
    inline double FRelative;

    void IInitialize();
    void IUpdate();
    void IDeinitialize();
}