#include"Client.hxx"

namespace NOppression::NClient
{
    SSpace::SSpace()
    {
        for
        (
            std::int64_t LCode{0} ; auto const& LName : std::initializer_list<std::string>
            {
                "Dimensionality"
                ,
                "TerrainArray"
                ,
                "EntityArray"
                ,
                "Order"
                ,
                "Entity"
            }
        )
        {
            FSignals[LName] = LCode++;
        }
        for
        (
            std::int64_t LCode{0} ; auto const& LAction : std::initializer_list<std::function<void(SSpace *const&)>>
            {
                &SSpace::IReactDimensionality
                ,
                &SSpace::IReactTerrainArray
                ,
                &SSpace::IReactEntityArray
                ,
                &SSpace::IReactSelection
            }
        )
        {
            FReactions[LCode++] = std::bind(LAction , this);
        }
        FX = 0;
        FY = 0;
        ISignalizeDimensionality();
        IReact();
        FTerrainArray.resize(FWidth * FHeight);
        ISignalizeTerrainArray();
        FEntityArray.resize(FWidth * FHeight);
        ISignalizeEntityArray();
        FMode = -1;
        FSelectionX = -1;
        FSelectionY = -1;
        FPartitionWidth = GVideo.FWidth / GVideo.FWidthProportional;
        FPartitionHeight = GVideo.FHeight / GVideo.FHeightProportional;
        for(std::int64_t LY{0} ; LY < GVideo.FHeightProportional ; LY++)
        {
            for(std::int64_t LX{0} ; LX < GVideo.FWidthProportional ; LX++)
            {
                FImages.emplace_back(LX * FPartitionWidth , LY * FPartitionHeight , FPartitionWidth , FPartitionHeight);
            }
        }
    }

    void SSpace::IUpdate()
    {
        if(GNetwork.IReady())
        {
            IReact();
        }
        FX = std::clamp<std::int64_t>(FX + (-static_cast<std::int64_t>(GKeyboard.FKeys["A"]->FState == "Pressed") + static_cast<std::int64_t>(GKeyboard.FKeys["D"]->FState == "Pressed")) , 0 , FWidth - GVideo.FWidthProportional);
        FY = std::clamp<std::int64_t>(FY + (-static_cast<std::int64_t>(GKeyboard.FKeys["W"]->FState == "Pressed") + static_cast<std::int64_t>(GKeyboard.FKeys["S"]->FState == "Pressed")) , 0 , FHeight - GVideo.FHeightProportional);
        for(std::int64_t LY{FY} ; LY < FY + GVideo.FHeightProportional ; LY++)
        {
            for(std::int64_t LX{FX} ; LX < FX + GVideo.FWidthProportional ; LX++)
            {
                FImages[(LY - FY) * GVideo.FWidthProportional + (LX - FX)].IDraw(LX , LY);
            }
        }
        switch(FMode)
        {
            case -1:
                if(FSelectionX != -1 && FSelectionY != -1)
                {
                    SDL_Rect LTarget
                    {
                        static_cast<std::int32_t>((FSelectionX - FX) * FPartitionWidth)
                        ,
                        static_cast<std::int32_t>((FSelectionY - FY) * FPartitionHeight)
                        ,
                        static_cast<std::int32_t>(FPartitionWidth)
                        ,
                        static_cast<std::int32_t>(FPartitionHeight)
                    };
                    SDL_SetRenderDrawColor(GVideo.FRenderer , 0 , 255 , 255 , 255);
                    SDL_RenderDrawRect(GVideo.FRenderer , &LTarget);
                    SDL_SetRenderDrawColor(GVideo.FRenderer , 0 , 0 , 0 , 255);
                }
            break;
            case 1:
                SDL_RenderCopy
                (
                    GVideo.FRenderer
                    ,
                    std::ranges::find_if(GVideo.FEntities , [&](auto const& AEntity){return(AEntity->FPath == "/Base/Construction.png");})->get()->FHandle
                    ,
                    nullptr
                    ,
                    &GSpace.FImages[GMouse.FCursor->FAbsolute->FPixel->FY / FPartitionHeight * GVideo.FWidthProportional + GMouse.FCursor->FAbsolute->FPixel->FX / FPartitionWidth].FTarget
                );
            break;
            case 2:
                SDL_RenderCopy
                (
                    GVideo.FRenderer
                    ,
                    std::ranges::find_if(GVideo.FEntities , [&](auto const& AEntity){return(AEntity->FPath == "/Builder/Construction.png");})->get()->FHandle
                    ,
                    nullptr
                    ,
                    &GSpace.FImages[GMouse.FCursor->FAbsolute->FPixel->FY / FPartitionHeight * GVideo.FWidthProportional + GMouse.FCursor->FAbsolute->FPixel->FX / FPartitionWidth].FTarget
                );
            break;
            case 3:
                SDL_RenderCopy
                (
                    GVideo.FRenderer
                    ,
                    std::ranges::find_if(GVideo.FEntities , [&](auto const& AEntity){return(AEntity->FPath == "/Miner/Construction.png");})->get()->FHandle
                    ,
                    nullptr
                    ,
                    &GSpace.FImages[GMouse.FCursor->FAbsolute->FPixel->FY / FPartitionHeight * GVideo.FWidthProportional + GMouse.FCursor->FAbsolute->FPixel->FX / FPartitionWidth].FTarget
                );
            break;
            case 4:
                SDL_RenderCopy
                (
                    GVideo.FRenderer
                    ,
                    std::ranges::find_if(GVideo.FEntities , [&](auto const& AEntity){return(AEntity->FPath == "/Tank/Construction.png");})->get()->FHandle
                    ,
                    nullptr
                    ,
                    &GSpace.FImages[GMouse.FCursor->FAbsolute->FPixel->FY / FPartitionHeight * GVideo.FWidthProportional + GMouse.FCursor->FAbsolute->FPixel->FX / FPartitionWidth].FTarget
                );
            break;
        }
        for
        (
            auto const& LKey : std::initializer_list<std::string>
            {
                "1"
                ,
                "2"
                ,
                "3"
                ,
                "4"
                ,
                "5"
                ,
                "6"
                ,
                "7"
                ,
                "8"
                ,
                "9"
                ,
                "0"
            }
        )
        {
            if(GKeyboard.FKeys[LKey]->FState == "Pressed" && FMode != std::stoll(LKey))
            {
                FMode = std::stoll(LKey);
                FSelectionX = -1;
                FSelectionY = -1;
            }
        }
        if(GMouse.FButtons["Left"]->FState == "Pressed")
        {
            switch(FMode)
            {
                case -1:
                    if
                    (
                        FEntityArray[(FY + GMouse.FCursor->FAbsolute->FPixel->FY / FPartitionHeight) * FWidth + (FX + GMouse.FCursor->FAbsolute->FPixel->FX / FPartitionWidth)]
                        ==
                        std::ranges::find_if(GVideo.FEntities , [&](auto const& AEntity){return(AEntity->FPath == "/_.png");}) - GVideo.FEntities.begin()
                    )
                    {
                        FSelectionX = -1;
                        FSelectionY = -1;
                    }
                    else
                    {
                        FSelectionX = FX + GMouse.FCursor->FAbsolute->FPixel->FX / FPartitionWidth;
                        FSelectionY = FY + GMouse.FCursor->FAbsolute->FPixel->FY / FPartitionHeight;
                    }
                break;
                case 1:
                    ISignalizeEntity(std::ranges::find_if(GVideo.FEntities , [&](auto const& AEntity){return(AEntity->FPath == "/Base/Building.png");}) - GVideo.FEntities.begin());
                break;
                case 2:
                    ISignalizeEntity(std::ranges::find_if(GVideo.FEntities , [&](auto const& AEntity){return(AEntity->FPath == "/Builder/+0.png");}) - GVideo.FEntities.begin());
                break;
                case 3:
                    ISignalizeEntity(std::ranges::find_if(GVideo.FEntities , [&](auto const& AEntity){return(AEntity->FPath == "/Miner/Building.png");}) - GVideo.FEntities.begin());
                break;
                case 4:
                    ISignalizeEntity(std::ranges::find_if(GVideo.FEntities , [&](auto const& AEntity){return(AEntity->FPath == "/Tank/+0.png");}) - GVideo.FEntities.begin());
                break;
            }
            FMode = -1;
        }
        if(GMouse.FButtons["Right"]->FState == "Pressed")
        {
            if(FMode == -1 && FSelectionX != -1 && FSelectionY != -1)
            {
                ISignalizeOrder();
            }
            FMode = -1;
        }
    }

    void SSpace::ISignalize(std::string const& AName , void const*const& AData , std::int64_t const& ASize)
    {
        std::vector<std::uint8_t> LRequest;
        LRequest.resize(sizeof(decltype(FSignals)::mapped_type) + ASize);
        std::memcpy(&LRequest[0] , &FSignals[AName] , sizeof(decltype(FSignals)::mapped_type));
        if(AData && ASize)
        {
            std::memcpy(&LRequest[sizeof(decltype(FSignals)::mapped_type)] , AData , ASize);
        }
        GNetwork.ISend(LRequest.data() , std::ssize(LRequest));
    }

    void SSpace::ISignalizeDimensionality()
    {
        ISignalize("Dimensionality");
    }

    void SSpace::ISignalizeTerrainArray()
    {
        ISignalize("TerrainArray");
    }

    void SSpace::ISignalizeEntityArray()
    {
        ISignalize("EntityArray");
    }

    void SSpace::ISignalizeOrder()
    {
        ISignalize("Order");
        struct SOrder
        {
            std::int64_t FFromX;
            std::int64_t FFromY;
            std::int64_t FToX;
            std::int64_t FToY;
        }
        LOrder{FSelectionX , FSelectionY , FX + GMouse.FCursor->FAbsolute->FPixel->FX / FPartitionWidth , FY + GMouse.FCursor->FAbsolute->FPixel->FY / FPartitionHeight};
        GNetwork.ISend(&LOrder , sizeof(LOrder));
    }

    void SSpace::ISignalizeEntity(std::int64_t const& ACode)
    {
        ISignalize("Entity");
        struct SEntity
        {
            std::int64_t FX;
            std::int64_t FY;
            std::int64_t FCode;
        }
        LEntity{FX + GMouse.FCursor->FAbsolute->FPixel->FX / FPartitionWidth , FY + GMouse.FCursor->FAbsolute->FPixel->FY / FPartitionHeight , ACode};
        GNetwork.ISend(&LEntity , sizeof(LEntity));
    }

    void SSpace::IReact()
    {
        std::int64_t LRequest;
        GNetwork.IReceiveIntegral(LRequest);
        FReactions[LRequest]();
    }

    void SSpace::IReactDimensionality()
    {
        struct SDimensionality
        {
            std::int64_t FX;
            std::int64_t FY;
        }
        LDimensionality;
        GNetwork.IReceive(&LDimensionality , sizeof(LDimensionality));
        FWidth = LDimensionality.FX;
        FHeight = LDimensionality.FY;
    }

    void SSpace::IReactTerrainArray()
    {
        GNetwork.IReceive(FTerrainArray.data() , FWidth * FHeight * sizeof(decltype(FTerrainArray)::value_type));
        ISignalizeTerrainArray();
    }

    void SSpace::IReactEntityArray()
    {
        GNetwork.IReceive(FEntityArray.data() , FWidth * FHeight * sizeof(decltype(FEntityArray)::value_type));
        ISignalizeEntityArray();
    }

    void SSpace::IReactSelection()
    {
        struct SSelection
        {
            std::int64_t FX;
            std::int64_t FY;
        }
        LSelection;
        GNetwork.IReceive(&LSelection , sizeof(LSelection));
        FSelectionX = LSelection.FX;
        FSelectionY = LSelection.FY;
    }
}