#include"Server.hxx"
#include"Selection.hxx"

namespace NOppression::NServer::NSpace::NSelection
{
    void IInitialize()
    {
        GSelectionArray[0] = nullptr;
        GSelection = 0;
        GX = 0;
        GY = 0;
    }
    
    void IConstruct()
    {
        for(std::int64_t LSelectionArrayIndex{0} ; LSelectionArrayIndex <= std::ssize(GSelectionArray) ; LSelectionArrayIndex++)
        {
            if(!GSelectionArray.contains(LSelectionArrayIndex))
            {
                GSelection = LSelectionArrayIndex;
                break;
            }
        }
        GSelectionArray[GSelection] = new SSelection;
        GSelectionArray[GSelection]->FX = GX;
        GSelectionArray[GSelection]->FY = GY;
    }

    void IDeconstruct()
    {
        delete GSelectionArray[GSelection];
        GSelectionArray.erase(GSelection);
    }

    void IDeinitialize()
    {
        GY = 0;
        GX = 0;
        GSelection = 0;
        GSelectionArray.clear();
    }
}