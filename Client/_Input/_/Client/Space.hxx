#pragma once

namespace NOppression::NClient
{
    inline struct SSpace
    {
        std::unordered_map<std::string , std::int64_t> FSignals;
        std::unordered_map<std::int64_t , std::function<void()>> FReactions;
        std::int64_t FX;
        std::int64_t FY;
        struct SDimensions
        {
            std::int64_t FX;
            std::int64_t FY;
        }
        FDimensions;
        std::vector<std::int64_t> FTerrains;
        std::vector<std::int64_t> FEntities;
        struct SSelection
        {
            std::int64_t FX;
            std::int64_t FY;
        }
        FSelection;
        std::int64_t FPartitionWidth;
        std::int64_t FPartitionHeight;
        std::vector<NSpace::SImage> FImages;

        SSpace();
        void IUpdate();
        void ISignalize(std::string const& AName , void const*const& AData = nullptr , std::int64_t const& ASize = 0);
        void ISignalizeDimensions();
        void ISignalizeTerrains();
        void ISignalizeEntities();
        void ISignalizeMovement();
        void IReact();
        void IReactDimensions();
        void IReactTerrains();
        void IReactEntities();
        void IReactMovement();
    }
    GSpace;
}