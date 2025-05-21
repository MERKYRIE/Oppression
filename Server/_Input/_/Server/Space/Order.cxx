#include"Server.hxx"
#include"Order.hxx"

#include"../Space.hxx"
#include"../Time.hxx"

#include"Entity.hxx"
#include"Selection.hxx"

namespace NOppression::NServer::NSpace::NOrder
{
    void IInitialize()
    {
        GOrderArray[0] = nullptr;
        GOrder = 0;
        GFromX = 0;
        GFromY = 0;
        GToX = 0;
        GToY = 0;
        GDuration = 0.0;
        GIsCompleted = false;
    }
    
    void IConstruct()
    {
        for(std::int64_t LOrderArrayIndex{0} ; LOrderArrayIndex <= std::ssize(GOrderArray) ; LOrderArrayIndex++)
        {
            if(!GOrderArray.contains(LOrderArrayIndex))
            {
                GOrder = LOrderArrayIndex;
                break;
            }
        }
        GOrderArray[GOrder] = new SOrder;
        GOrderArray[GOrder]->FFromX = GFromX;
        GOrderArray[GOrder]->FFromY = GFromY;
        GOrderArray[GOrder]->FToX = GToX;
        GOrderArray[GOrder]->FToY = GToY;
        GOrderArray[GOrder]->FTimer = 0.0;
        GOrderArray[GOrder]->FDuration = GDuration;
    }

    void IUpdate()
    {
        GOrderArray[GOrder]->FTimer += NTime::GRelative;
        if(GOrderArray[GOrder]->FTimer > GOrderArray[GOrder]->FDuration)
        {
            std::int64_t LLastX{GOrderArray[GOrder]->FFromX};
            char LDeltaX{'0'};
            if(GOrderArray[GOrder]->FToX - GOrderArray[GOrder]->FFromX < 0)
            {
                LDeltaX = '-';
                GOrderArray[GOrder]->FFromX--;
            }
            if(GOrderArray[GOrder]->FToX - GOrderArray[GOrder]->FFromX > 0)
            {
                LDeltaX = '+';
                GOrderArray[GOrder]->FFromX++;
            }
            std::int64_t LLastY{GOrderArray[GOrder]->FFromY};
            char LDeltaY{'0'};
            if(GOrderArray[GOrder]->FToY - GOrderArray[GOrder]->FFromY < 0)
            {
                LDeltaY = '-';
                GOrderArray[GOrder]->FFromY--;
            }
            if(GOrderArray[GOrder]->FToY - GOrderArray[GOrder]->FFromY > 0)
            {
                LDeltaY = '+';
                GOrderArray[GOrder]->FFromY++;
            }
            std::swap(GSpace.GEntityCodeArray[LLastY * GSpace.GWidth + LLastX] , GSpace.GEntityCodeArray[GOrderArray[GOrder]->FFromY * GSpace.GWidth + GOrderArray[GOrder]->FFromX]);
            NEntity::GEntity = GSpace.GEntityCodeArray[GOrderArray[GOrder]->FFromY * GSpace.GWidth + GOrderArray[GOrder]->FFromX];
            NEntity::IName();
            NEntity::GName = NEntity::GName.substr(0 , NEntity::GName.find('/' , 1) + 1) + LDeltaX + LDeltaY + ".png";
            NEntity::IDeconstruct();
            NEntity::IConstruct();
            NSelection::GX = GOrderArray[GOrder]->FFromX;
            NSelection::GY = GOrderArray[GOrder]->FFromY;
            NSelection::IConstruct();
            GSpace.GSelection = NSelection::GSelection;
            GSpace.ISignalizeSelection();
            NSelection::IDeconstruct();
            if(GOrderArray[GOrder]->FFromX != GOrderArray[GOrder]->FToX || GOrderArray[GOrder]->FFromY != GOrderArray[GOrder]->FToY)
            {
                GOrderArray[GOrder]->FTimer = 0.0;
            }
        }
    }

    void IIsCompleted()
    {
        GIsCompleted = GOrderArray[GOrder]->FTimer > GOrderArray[GOrder]->FDuration;
    }

    void IDeconstruct()
    {
        delete GOrderArray[GOrder];
        GOrderArray.erase(GOrder);
    }

    void IDeinitialize()
    {
        GIsCompleted = false;
        GDuration = 0.0;
        GToY = 0;
        GToX = 0;
        GFromY = 0;
        GFromX = 0;
        GOrder = 0;
        GOrderArray.clear();
    }
}