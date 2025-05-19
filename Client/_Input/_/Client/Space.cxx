#include"Client.hxx"

namespace NOppression::NClient
{
    SSpace::SSpace()
    {
        for
        (
            std::int64_t LCode{0} ; auto const& LName : std::initializer_list<std::string>
            {
                "Dimensions"
                ,
                "Terrains"
                ,
                "Entities"
                ,
                "Movement"
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
                &SSpace::IReactDimensions
                ,
                &SSpace::IReactTerrains
                ,
                &SSpace::IReactEntities
                ,
                &SSpace::IReactMovement
            }
        )
        {
            FReactions[LCode++] = std::bind(LAction , this);
        }
        FX = 0;
        FY = 0;
        ISignalizeDimensions();
        IReact();
        FTerrains.resize(FDimensions.FX * FDimensions.FY);
        ISignalizeTerrains();
        FEntities.resize(FDimensions.FX * FDimensions.FY);
        ISignalizeEntities();
        FMode = -1;
        FSelection.FX = -1;
        FSelection.FY = -1;
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
        FX = std::clamp<std::int64_t>(FX + (-static_cast<std::int64_t>(GKeyboard.FKeys["A"]->FState == "Pressed") + static_cast<std::int64_t>(GKeyboard.FKeys["D"]->FState == "Pressed")) , 0 , FDimensions.FX - GVideo.FWidthProportional);
        FY = std::clamp<std::int64_t>(FY + (-static_cast<std::int64_t>(GKeyboard.FKeys["W"]->FState == "Pressed") + static_cast<std::int64_t>(GKeyboard.FKeys["S"]->FState == "Pressed")) , 0 , FDimensions.FY - GVideo.FHeightProportional);
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
                if(FSelection.FX != -1 && FSelection.FY != -1)
                {
                    SDL_Rect LTarget
                    {
                        static_cast<std::int32_t>((FSelection.FX - FX) * FPartitionWidth)
                        ,
                        static_cast<std::int32_t>((FSelection.FY - FY) * FPartitionHeight)
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
            }
        }
        if(GMouse.FButtons["Left"]->FState == "Pressed")
        {
            switch(FMode)
            {
                case -1:
                    if
                    (
                        FEntities[(FY + GMouse.FCursor->FAbsolute->FPixel->FY / FPartitionHeight) * FDimensions.FX + (FX + GMouse.FCursor->FAbsolute->FPixel->FX / FPartitionWidth)]
                        ==
                        std::ranges::find_if(GVideo.FEntities , [&](auto const& AEntity){return(AEntity->FPath == "/_.png");}) - GVideo.FEntities.begin()
                    )
                    {
                        FSelection.FX = -1;
                        FSelection.FY = -1;
                    }
                    else
                    {
                        FSelection.FX = FX + GMouse.FCursor->FAbsolute->FPixel->FX / FPartitionWidth;
                        FSelection.FY = FY + GMouse.FCursor->FAbsolute->FPixel->FY / FPartitionHeight;
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
            if(FMode == -1 && FSelection.FX != -1 && FSelection.FY != -1)
            {
                ISignalizeMovement();
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

    void SSpace::ISignalizeDimensions()
    {
        ISignalize("Dimensions");
    }

    void SSpace::ISignalizeTerrains()
    {
        ISignalize("Terrains");
    }

    void SSpace::ISignalizeEntities()
    {
        ISignalize("Entities");
    }

    void SSpace::ISignalizeMovement()
    {
        ISignalize("Movement");
        struct SMovement
        {
            std::int64_t FSelectionX;
            std::int64_t FSelectionY;
            std::int64_t FOrderX;
            std::int64_t FOrderY;
        }
        LMovement{FSelection.FX , FSelection.FY , FX + GMouse.FCursor->FAbsolute->FPixel->FX / FPartitionWidth , FY + GMouse.FCursor->FAbsolute->FPixel->FY / FPartitionHeight};
        GNetwork.ISend(&LMovement , sizeof(LMovement));
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

    void SSpace::IReactDimensions()
    {
        GNetwork.IReceive(&FDimensions , sizeof(FDimensions));
    }

    void SSpace::IReactTerrains()
    {
        GNetwork.IReceive(FTerrains.data() , FDimensions.FX * FDimensions.FY * sizeof(decltype(FTerrains)::value_type));
        ISignalizeTerrains();
    }

    void SSpace::IReactEntities()
    {
        GNetwork.IReceive(FEntities.data() , FDimensions.FX * FDimensions.FY * sizeof(decltype(FEntities)::value_type));
        ISignalizeEntities();
    }

    void SSpace::IReactMovement()
    {
        GNetwork.IReceive(&FSelection , sizeof(FSelection));
    }
}