#pragma once

namespace NOppression::NServer::NSpace
{
    struct STerrain
    {
        std::int64_t FCode;
        
        STerrain(std::string const& AName = "/_.png");
        void IUpdate();
    };
}