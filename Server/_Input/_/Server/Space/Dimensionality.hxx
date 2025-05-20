#pragma once

namespace NOppression::NServer::NSpace::NDimensionality
{
    struct SDimensionality
    {
        std::int64_t FX;
        std::int64_t FY;
    };

    inline std::unordered_map<std::int64_t , SDimensionality *> GDimensionalityArray;
    inline std::int64_t GDimensionality;
    inline std::int64_t GX;
    inline std::int64_t GY;
        
    void IInitialize();
    void IConstruct();
    void IDeconstruct();
    void IDeinitialize();
}