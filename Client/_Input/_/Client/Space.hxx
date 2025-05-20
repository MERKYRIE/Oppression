#pragma once

namespace NOppression::NClient
{
    inline struct SSpace
    {
        std::unordered_map<std::string , std::int64_t> FSignals;
        std::unordered_map<std::int64_t , std::function<void()>> FReactions;
        std::int64_t FX;
        std::int64_t FY;
        std::int64_t FWidth;
        std::int64_t FHeight;
        std::vector<std::int64_t> FTerrainArray;
        std::vector<std::int64_t> FEntityArray;
        std::int64_t FMode;
        std::int64_t FSelectionX;
        std::int64_t FSelectionY;
        std::int64_t FPartitionWidth;
        std::int64_t FPartitionHeight;
        std::vector<NSpace::SImage> FImages;

        SSpace();
        void IUpdate();
        void ISignalize(std::string const& AName , void const*const& AData = nullptr , std::int64_t const& ASize = 0);
        void ISignalizeDimensionality();
        void ISignalizeTerrainArray();
        void ISignalizeEntityArray();
        void ISignalizeOrder();
        void ISignalizeEntity(std::int64_t const& ACode);
        void IReact();
        void IReactDimensionality();
        void IReactTerrainArray();
        void IReactEntityArray();
        void IReactSelection();
    }
    GSpace;
}