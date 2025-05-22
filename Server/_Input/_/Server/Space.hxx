#pragma once

namespace NOppression::NServer::NSpace
{
    struct SSpace
    {
        struct SSignalType
        {
            std::int64_t FDimensionality;
            std::int64_t FTerrainArray;
            std::int64_t FEntityArray;
            std::int64_t FSelection;
        };
        
        std::int64_t FCode;
        SSignalType FSignalType;
        std::unordered_map<std::int64_t , std::function<void()>> FReactionCodeToActionArray;
        std::int64_t FWidth;
        std::int64_t FHeight;
        std::fstream FFile;
        std::unordered_map<std::string , std::int64_t> FTerrainNameToCodeArray;
        std::vector<std::int64_t> FTerrainCodeArray;
        std::vector<NTerrain::STerrain> FTerrainArray;
        std::unordered_map<std::string , std::int64_t> FEntityNameToCodeArray;
        std::vector<std::int64_t> FEntityCodeArray;
        std::vector<NEntity::SEntity> FEntityArray;
        std::vector<std::int64_t> FOrderCodeArray;
        bool FIsRemoved;
        std::vector<std::uint8_t> FByteArray;
        std::int64_t FSignal;
        void * FData;
        std::int64_t FSize;
        std::int64_t FSelection;

        void IInitialize();
        void IUpdate();
        void ISignalize();
        void ISignalizeDimensionality();
        void ISignalizeTerrainArray();
        void ISignalizeEntityArray();
        void ISignalizeSelection();
        void IReact();
        void IReactDimensionality();
        void IReactTerrainArray();
        void IReactEntitieArray();
        void IReactOrder();
        void IReactEntity();
        void IDeinitialize();
    };
}