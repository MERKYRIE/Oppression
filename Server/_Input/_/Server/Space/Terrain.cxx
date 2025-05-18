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
}