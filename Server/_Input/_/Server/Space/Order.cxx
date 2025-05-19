#include"Server.hxx"

namespace NOppression::NServer::NSpace
{
    SOrder::SOrder(std::int64_t const& AFromX , std::int64_t const& AFromY , std::int64_t const& AToX , std::int64_t const& AToY , double const& ADuration)
    {
        FFromX = AFromX;
        FFromY = AFromY;
        FToX = AToX;
        FToY = AToY;
        FTimer = 0.0;
        FDuration = ADuration;
    }
    
    void SOrder::IUpdate()
    {
        FTimer += GTime.FRelative;
        if(FTimer > FDuration)
        {
            std::int64_t LLastX{FFromX};
            char LDeltaX{'0'};
            if(FToX - FFromX < 0)
            {
                LDeltaX = '-';
                FFromX--;
            }
            if(FToX - FFromX > 0)
            {
                LDeltaX = '+';
                FFromX++;
            }
            std::int64_t LLastY{FFromY};
            char LDeltaY{'0'};
            if(FToY - FFromY < 0)
            {
                LDeltaY = '-';
                FFromY--;
            }
            if(FToY - FFromY > 0)
            {
                LDeltaY = '+';
                FFromY++;
            }
            std::swap(GSpace.FEntities[LLastY * GSpace.FDimensions.FX + LLastX] , GSpace.FEntities[FFromY * GSpace.FDimensions.FX + FFromX]);
            GSpace.FEntities[FFromY * GSpace.FDimensions.FX + FFromX]
            =
            GSpace.FEntities[FFromY * GSpace.FDimensions.FX + FFromX].IName().substr(0 , GSpace.FEntities[FFromY * GSpace.FDimensions.FX + FFromX].IName().find('/' , 1) + 1)
            +
            LDeltaX
            +
            LDeltaY
            +
            ".png";
            GSpace.ISignalizeMovement({FFromX , FFromY});
            if(FFromX != FToX || FFromY != FToY)
            {
                FTimer = 0.0;
            }
        }
    }

    bool SOrder::ICompleted()
    {
        return(FTimer > FDuration);
    }
}