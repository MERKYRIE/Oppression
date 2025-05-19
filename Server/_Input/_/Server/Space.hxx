#pragma once

namespace NOppression::NServer::NSpace
{
    inline std::unordered_map<std::string , std::int64_t> FSignalArray;
    inline std::unordered_map<std::int64_t , std::function<void()>> FReactionArray;
    inline std::int64_t FWidth;
    inline std::int64_t FHeight;
    inline std::unordered_map<std::string , std::int64_t> FTerrainAdaptorArray;
    inline std::vector<NSpace::STerrain> FTerrainArray;
    inline std::unordered_map<std::string , std::int64_t> FEntityAdaptorArray;
    inline std::vector<NSpace::SEntity> FEntityArray;
    inline std::vector<NSpace::SOrder> FOrderArray;

    void IInitialize();
    void IUpdate();
    void ISignalize(std::string const& AName , void const*const& AData = nullptr , std::int64_t const& ASize = 0);
    void ISignalizeDimensions();
    void ISignalizeTerrains();
    void ISignalizeEntities();
    void ISignalizeMovement(NSpace::SSelection const& ASelection);
    void IReact();
    void IReactDimensions();
    void IReactTerrains();
    void IReactEntities();
    void IReactMovement();
    void IReactEntity();
}