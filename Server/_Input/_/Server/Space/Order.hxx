#pragma once

namespace NOppression::NServer::NSpace::NOrder
{
    struct SOrder
    {
        std::int64_t FFromX;
        std::int64_t FFromY;
        std::int64_t FToX;
        std::int64_t FToY;
        double FTimer;
        double FDuration;
    };

    inline std::unordered_map<std::int64_t , SOrder *> GOrderArray;
    inline std::int64_t GOrder;
    inline std::int64_t GFromX;
    inline std::int64_t GFromY;
    inline std::int64_t GToX;
    inline std::int64_t GToY;
    inline double GDuration;
    inline bool GIsCompleted;

    void IInitialize();
    void IConstruct();
    void IUpdate();
    void IIsCompleted();
    void IDeconstruct();
    void IDeinitialize();
}