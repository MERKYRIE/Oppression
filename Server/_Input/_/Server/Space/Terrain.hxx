#pragma once

namespace NOppression::NServer::NSpace::NTerrain
{
    struct STerrain
    {
        std::int64_t FCode;
    };

    inline std::unordered_map<std::int64_t , STerrain *> GTerrainArray;
    inline std::int64_t GTerrain;
    inline std::string GName;
        
    void IInitialize();
    void IConstruct();
    void IName();
    void IDeconstruct();
    void IDeinitialize();
}