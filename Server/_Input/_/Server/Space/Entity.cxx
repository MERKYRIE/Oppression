#include"Server.hxx"

namespace NOppression::NServer::NSpace
{
    SEntity::SEntity(std::string const& AName)
    {
        FCode = FEntityAdaptorArray[AName];
    }
    
    void SEntity::IUpdate()
    {
        
    }

    std::string SEntity::IName()
    {
        return(std::ranges::find_if(FEntityAdaptorArray , [&](auto const& AEntity){return(FCode == AEntity.second);})->first);
    }
}