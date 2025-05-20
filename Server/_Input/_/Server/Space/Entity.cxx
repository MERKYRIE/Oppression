#include"Server.hxx"

namespace NOppression::NServer::NSpace::NEntity
{
    void IInitialize()
    {
        GEntityArray[0] = nullptr;
        GEntity = 0;
        GName = "";
    }
    
    void IConstruct()
    {
        for(std::int64_t LEntityArrayIndex{0} ; LEntityArrayIndex <= std::ssize(GEntityArray) ; LEntityArrayIndex++)
        {
            if(!GEntityArray.contains(LEntityArrayIndex))
            {
                GEntity = LEntityArrayIndex;
                break;
            }
        }
        GEntityArray[GEntity] = new SEntity;
        GEntityArray[GEntity]->FCode = GEntityNameToCodeArray[GName];
    }

    void IName()
    {
        GName = std::ranges::find_if(GEntityNameToCodeArray , [&](auto const& AEntity){return(GEntityArray[GEntity]->FCode == AEntity.second);})->first;
    }

    void IDeconstruct()
    {
        delete GEntityArray[GEntity];
        GEntityArray.erase(GEntity);
    }

    void IDeinitialize()
    {
        GName = "";
        GEntity = 0;
        GEntityArray.clear();
    }
}