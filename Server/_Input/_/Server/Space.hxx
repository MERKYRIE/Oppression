#pragma once

namespace NOppression::NServer::NSpace
{
    inline std::int64_t GCode;
    inline std::unordered_map<std::string , std::int64_t> GSignalNameToCodeArray;
    inline std::unordered_map<std::int64_t , std::function<void()>> GReactionCodeToActionArray;
    inline std::int64_t GWidth;
    inline std::int64_t GHeight;
    inline std::fstream GFile;
    inline std::unordered_map<std::string , std::int64_t> GTerrainNameToCodeArray;
    inline std::vector<std::int64_t> GTerrainCodeArray;
    inline std::vector<NTerrain::STerrain> GTerrainArray;
    inline std::unordered_map<std::string , std::int64_t> GEntityNameToCodeArray;
    inline std::vector<std::int64_t> GEntityCodeArray;
    inline std::vector<NEntity::SEntity> GEntityArray;
    inline std::vector<std::int64_t> GOrderCodeArray;
    inline bool GIsRemoved;
    inline std::vector<std::uint8_t> GByteArray;
    inline std::string GName;
    inline void * GData;
    inline std::int64_t GSize;
    inline std::int64_t GSelection;

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