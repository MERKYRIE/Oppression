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
            FReactions[LCode] = std::bind(LAction , this);
            LCode++;
        }
        FX = 0;
        FY = 0;
        ISignalizeDimensions();
        IReact();
        FTerrains.resize(FDimensions.FX * FDimensions.FY);
        ISignalizeTerrains();
        FEntities.resize(FDimensions.FX * FDimensions.FY);
        ISignalizeEntities();
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
        if(GMouse.FButtons["Left"]->FState == "Pressed")
        {
            FSelection.FX = FX + GMouse.FCursor->FAbsolute->FPixel->FX / FPartitionWidth;
            FSelection.FY = FY + GMouse.FCursor->FAbsolute->FPixel->FY / FPartitionHeight;
        }
        SDL_Rect LTarget{static_cast<std::int32_t>((FSelection.FX - FX) * FPartitionWidth) , static_cast<std::int32_t>((FSelection.FY - FY) * FPartitionHeight) , static_cast<std::int32_t>(FPartitionWidth) , static_cast<std::int32_t>(FPartitionHeight)};
        SDL_SetRenderDrawColor(GVideo.FRenderer , 0 , 255 , 255 , 255);
        SDL_RenderDrawRect(GVideo.FRenderer , &LTarget);
        SDL_SetRenderDrawColor(GVideo.FRenderer , 0 , 0 , 0 , 255);
        if(GMouse.FButtons["Right"]->FState == "Pressed" && FSelection.FX != -1 && FSelection.FY != -1)
        {
            ISignalizeMovement();
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