#pragma once

namespace NOppression::NServer::NSpace::NEntity
{
    struct SEntity
    {
        std::int64_t FCode;
    };

    inline std::unordered_map<std::int64_t , SEntity *> GEntityArray;
    inline std::int64_t GEntity;
    inline std::string GName;
        
    void IInitialize();
    void IConstruct();
    void IName();
    void IDeconstruct();
    void IDeinitialize();
}