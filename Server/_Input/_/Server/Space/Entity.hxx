#pragma once

namespace NOppression::NServer::NSpace
{
    struct SEntity
    {
        std::int64_t FCode;
        
        SEntity(std::string const& AName = "/_.png");
        void IUpdate();
    };
}