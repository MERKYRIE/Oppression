#include"Server.hxx"

namespace NOppression::NServer::NSpace
{
    STerrain::STerrain(std::string const& AName)
    {
        FCode = GSpace.FTerrainAdaptors[AName];
    }
    
    void STerrain::IUpdate()
    {
        
    }

    std::string STerrain::IName()
    {
        return(std::ranges::find_if(GSpace.FTerrainAdaptors , [&](auto const& ATerrain){return(FCode == ATerrain.second);})->first);
    }
}