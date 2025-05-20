#include"Server.hxx"

namespace NOppression::NServer::NSpace::NTerrain
{
    void IInitialize()
    {
        GTerrainArray[0] = nullptr;
        GTerrain = 0;
        GName = "";
    }
    
    void IConstruct()
    {
        GTerrain = std::ranges::max_element(GTerrainArray)->first + 1;
        GTerrainArray[GTerrain] = new STerrain;
        GTerrainArray[GTerrain]->FCode = FTerrainAdaptorArray[GName];
    }

    void IName()
    {
        GName = std::ranges::find_if(FTerrainAdaptorArray , [&](auto const& ATerrain){return(GTerrainArray[GTerrain]->FCode == ATerrain.second);})->first;
    }

    void IDeconstruct()
    {
        delete GTerrainArray[GTerrain];
        GTerrainArray.erase(GTerrain);
    }

    void IDeinitialize()
    {
        GName = "";
        GTerrain = 0;
        GTerrainArray.clear();
    }
}