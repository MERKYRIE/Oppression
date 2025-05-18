#include"Server.hxx"

namespace NOppression::NServer::NSpace
{
    SEntity::SEntity(std::string const& AName)
    {
        FCode = GSpace.FEntityAdaptors[AName];
    }
    
    void SEntity::IUpdate()
    {
        
    }
}