#include"Server.hxx"
#include"Dimensionality.hxx"

namespace NOppression::NServer::NSpace::NDimensionality
{
    void IInitialize()
    {
        GDimensionalityArray[0] = nullptr;
        GDimensionality = 0;
        GX = 0;
        GY = 0;
    }
    
    void IConstruct()
    {
        for(std::int64_t LDimensionalityArrayIndex{0} ; LDimensionalityArrayIndex <= std::ssize(GDimensionalityArray) ; LDimensionalityArrayIndex++)
        {
            if(!GDimensionalityArray.contains(LDimensionalityArrayIndex))
            {
                GDimensionality = LDimensionalityArrayIndex;
                break;
            }
        }
        GDimensionalityArray[GDimensionality] = new SDimensionality;
        GDimensionalityArray[GDimensionality]->FX = GX;
        GDimensionalityArray[GDimensionality]->FY = GY;
    }

    void IDeconstruct()
    {
        delete GDimensionalityArray[GDimensionality];
        GDimensionalityArray.erase(GDimensionality);
    }

    void IDeinitialize()
    {
        GY = 0;
        GX = 0;
        GDimensionality = 0;
        GDimensionalityArray.clear();
    }
}