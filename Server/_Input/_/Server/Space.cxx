#include"Server.hxx"

namespace NOppression::NServer
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
            std::int64_t LCode{0} ; auto const& LAction : std::initializer_list<std::function<void(SSpace *const& , NNetwork::SClient &)>>
            {
                &SSpace::IReactDimensions
                ,
                &SSpace::IReactTerrains
                ,
                &SSpace::IReactEntities
                ,
                &SSpace::IReactMovement
                ,
                &SSpace::IReactEntity
            }
        )
        {
            FReactions[LCode++] = std::bind(LAction , this , std::placeholders::_1);
        }
        FDimensions.FX = 40;
        FDimensions.FY = 60;
        for(std::int64_t LCode{0} ; auto const& LEntry : std::filesystem::recursive_directory_iterator{"Images/Terrains"})
        {
            if(LEntry.path().extension() == ".png")
            {
                FTerrainAdaptors[LEntry.path().generic_string().substr(LEntry.path().generic_string().find('/' , LEntry.path().generic_string().find('/') + 1))] = LCode++;
            }
        }
        FTerrains.resize(FDimensions.FX * FDimensions.FY);
        {
            std::fstream LStream{"Terrains/Antifreeze.txt" , std::ios::in};
            std::string LString;
            for(std::int64_t LY{0} ; LY < FDimensions.FY ; LY++)
            {
                for(std::int64_t LX{0} ; LX < FDimensions.FX ; LX++)
                {
                    LStream >> LString;
                    FTerrains[LY * FDimensions.FX + LX] = LString;
                }
            }
        }
        for(std::int64_t LCode{0} ; auto const& LEntry : std::filesystem::recursive_directory_iterator{"Images/Entities"})
        {
            if(LEntry.path().extension() == ".png")
            {
                FEntityAdaptors[LEntry.path().generic_string().substr(LEntry.path().generic_string().find('/' , LEntry.path().generic_string().find('/') + 1))] = LCode++;
            }
        }
        FEntities.resize(FDimensions.FX * FDimensions.FY);
        //FEntities[20 * FDimensions.FX + 20] = std::string{"/Builder/0+.png"};
    }

    void SSpace::IUpdate()
    {
        IReact();
        std::ranges::for_each(FOrders , [&](auto & AOrder){AOrder.IUpdate();});
        bool LRemoved;
        do
        {
            LRemoved = false;
            for(auto LOrder{FOrders.begin()} ; LOrder != FOrders.end() ; LOrder++)
            {
                if(LOrder->ICompleted())
                {
                    FOrders.erase(LOrder);
                    LRemoved = true;
                    break;
                }
            }
        }
        while(LRemoved);
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
        ISignalize("Dimensions" , &FDimensions , sizeof(FDimensions));
    }

    void SSpace::ISignalizeTerrains()
    {
        ISignalize("Terrains" , FTerrains.data() , FDimensions.FX * FDimensions.FY * sizeof(decltype(FTerrains)::value_type));
    }

    void SSpace::ISignalizeEntities()
    {
        ISignalize("Entities" , FEntities.data() , FDimensions.FX * FDimensions.FY * sizeof(decltype(FEntities)::value_type));
    }

    void SSpace::ISignalizeMovement(NSpace::SSelection const& ASelection)
    {
        ISignalize("Movement" , &ASelection , sizeof(ASelection));
    }

    void SSpace::IReact()
    {
        GNetwork.IAddressAll();
        std::vector<std::int64_t> LRequests;
        GNetwork.IReceiveIntegral(LRequests);
        for(std::int64_t LRequest{0} ; LRequest < std::ssize(LRequests) ; LRequest++)
        {
            FReactions[LRequests[LRequest]](GNetwork.FClients[LRequest]);
        }
    }

    void SSpace::IReactDimensions(NNetwork::SClient & AClient)
    {
        GNetwork.IAddressOne(AClient);
        ISignalizeDimensions();
    }

    void SSpace::IReactTerrains(NNetwork::SClient & AClient)
    {
        GNetwork.IAddressOne(AClient);
        ISignalizeTerrains();
    }

    void SSpace::IReactEntities(NNetwork::SClient & AClient)
    {
        GNetwork.IAddressOne(AClient);
        ISignalizeEntities();
    }

    void SSpace::IReactMovement(NNetwork::SClient & AClient)
    {
        GNetwork.IAddressOne(AClient);
        struct SMovement
        {
            std::int64_t FSelectionX;
            std::int64_t FSelectionY;
            std::int64_t FOrderX;
            std::int64_t FOrderY;
        }
        LMovement;
        GNetwork.IReceive(&LMovement , sizeof(LMovement));
        if(FEntities[LMovement.FSelectionY * FDimensions.FX + LMovement.FSelectionX].IName() != "/_.png")
        {
            FOrders.emplace_back(LMovement.FSelectionX , LMovement.FSelectionY , LMovement.FOrderX , LMovement.FOrderY , 1'000.0);
        }
    }

    void SSpace::IReactEntity(NNetwork::SClient & AClient)
    {
        GNetwork.IAddressOne(AClient);
        struct SEntity
        {
            std::int64_t FX;
            std::int64_t FY;
            std::int64_t FCode;
        }
        LEntity;
        GNetwork.IReceive(&LEntity , sizeof(LEntity));
        FEntities[LEntity.FY * FDimensions.FX + LEntity.FX].FCode = LEntity.FCode; 
    }
}