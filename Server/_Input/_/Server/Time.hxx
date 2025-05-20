#pragma once

namespace NOppression::NServer::NTime
{
    inline double GLast;
    inline double GAbsolute;
    inline double GRelative;

    void IInitialize();
    void IUpdate();
    void IDeinitialize();
}