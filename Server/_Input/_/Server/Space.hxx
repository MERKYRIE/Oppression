#pragma once

namespace NOppression::NServer::NSpace
{
    struct SSS
    {
        std::int64_t FOne{1};
        std::int64_t FTwo{2};
        std::int64_t FThree{3};
    };
    
    struct SSpace
    {
        std::int64_t GCode;
        std::unordered_map<std::string , std::int64_t> GSignalNameToCodeArray;
        std::unordered_map<std::int64_t , std::function<void()>> GReactionCodeToActionArray;
        std::int64_t GWidth;
        std::int64_t GHeight;
        std::fstream GFile;
        std::unordered_map<std::string , std::int64_t> GTerrainNameToCodeArray;
        std::vector<std::int64_t> GTerrainCodeArray;
        std::vector<NTerrain::STerrain> GTerrainArray;
        std::unordered_map<std::string , std::int64_t> GEntityNameToCodeArray;
        std::vector<std::int64_t> GEntityCodeArray;
        std::vector<NEntity::SEntity> GEntityArray;
        std::vector<std::int64_t> GOrderCodeArray;
        bool GIsRemoved;
        std::vector<std::uint8_t> GByteArray;
        std::string GName;
        void * GData;
        std::int64_t GSize;
        std::int64_t GSelection;

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
    }
    extern GSpace;
}