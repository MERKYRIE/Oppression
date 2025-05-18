#pragma once

namespace NOppression::NServer
{
    inline struct SSpace
    {
        std::unordered_map<std::string , std::int64_t> FSignals;
        std::unordered_map<std::int64_t , std::function<void(NNetwork::SClient &)>> FReactions;
        struct SDimensions
        {
            std::int64_t FX;
            std::int64_t FY;
        }
        FDimensions;
        std::unordered_map<std::string , std::int64_t> FTerrainAdaptors;
        std::vector<NSpace::STerrain> FTerrains;
        std::unordered_map<std::string , std::int64_t> FEntityAdaptors;
        std::vector<NSpace::SEntity> FEntities;
        std::vector<NSpace::SOrder> FOrders;

        SSpace();
        void IUpdate();
        void ISignalize(std::string const& AName , void const*const& AData = nullptr , std::int64_t const& ASize = 0);
        void ISignalizeDimensions();
        void ISignalizeTerrains();
        void ISignalizeEntities();
        void ISignalizeMovement(NSpace::SSelection const& ASelection);
        void IReact();
        void IReactDimensions(NNetwork::SClient & AClient);
        void IReactTerrains(NNetwork::SClient & AClient);
        void IReactEntities(NNetwork::SClient & AClient);
        void IReactMovement(NNetwork::SClient & AClient);
    }
    GSpace;
}