#include"Server.hxx"

namespace NOppression::NServer::NSpace
{
    void IInitialize()
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
            FSignalArray[LName] = LCode++;
        }
        for
        (
            std::int64_t LCode{0} ; auto const& LAction : std::initializer_list<std::function<void()>>
            {
                &IReactDimensions
                ,
                &IReactTerrains
                ,
                &IReactEntities
                ,
                &IReactMovement
                ,
                &IReactEntity
            }
        )
        {
            FReactionArray[LCode++] = std::bind(LAction);
        }
        FWidth = 40;
        FHeight = 60;
        for(std::int64_t LCode{0} ; auto const& LEntry : std::filesystem::recursive_directory_iterator{"Images/Terrains"})
        {
            if(LEntry.path().extension() == ".png")
            {
                FTerrainAdaptorArray[LEntry.path().generic_string().substr(LEntry.path().generic_string().find('/' , LEntry.path().generic_string().find('/') + 1))] = LCode++;
            }
        }
        FTerrainArray.resize(FWidth * FHeight);
        {
            std::fstream LStream{"Terrains/Antifreeze.txt" , std::ios::in};
            std::string LString;
            for(std::int64_t LY{0} ; LY < FHeight ; LY++)
            {
                for(std::int64_t LX{0} ; LX < FWidth ; LX++)
                {
                    LStream >> LString;
                    FTerrainArray[LY * FWidth + LX] = LString;
                }
            }
        }
        for(std::int64_t LCode{0} ; auto const& LEntry : std::filesystem::recursive_directory_iterator{"Images/Entities"})
        {
            if(LEntry.path().extension() == ".png")
            {
                FEntityAdaptorArray[LEntry.path().generic_string().substr(LEntry.path().generic_string().find('/' , LEntry.path().generic_string().find('/') + 1))] = LCode++;
            }
        }
        FEntityArray.resize(FWidth * FHeight);
        //FEntities[20 * FDimensions.FX + 20] = std::string{"/Builder/0+.png"};
    }

    void IUpdate()
    {
        IReact();
        std::ranges::for_each(FOrderArray , [&](auto & AOrder){AOrder.IUpdate();});
        bool LRemoved;
        do
        {
            LRemoved = false;
            for(auto LOrder{FOrderArray.begin()} ; LOrder != FOrderArray.end() ; LOrder++)
            {
                if(LOrder->ICompleted())
                {
                    FOrderArray.erase(LOrder);
                    LRemoved = true;
                    break;
                }
            }
        }
        while(LRemoved);
    }

    void ISignalize(std::string const& AName , void const*const& AData , std::int64_t const& ASize)
    {
        std::vector<std::uint8_t> LSignal;
        LSignal.resize(sizeof(decltype(FSignalArray)::mapped_type) + ASize);
        std::memcpy(&LSignal[0] , &FSignalArray[AName] , sizeof(decltype(FSignalArray)::mapped_type));
        if(AData && ASize)
        {
            std::memcpy(&LSignal[sizeof(decltype(FSignalArray)::mapped_type)] , AData , ASize);
        }
        NNetwork::ISend(LSignal.data() , std::ssize(LSignal));
    }

    void ISignalizeDimensions()
    {
        struct SDimensions
        {
            std::int64_t FX;
            std::int64_t FY;
        }
        LDimensions{FWidth , FHeight};
        ISignalize("Dimensions" , &LDimensions , sizeof(LDimensions));
    }

    void ISignalizeTerrains()
    {
        ISignalize("Terrains" , FTerrainArray.data() , FWidth * FHeight * sizeof(decltype(FTerrainArray)::value_type));
    }

    void ISignalizeEntities()
    {
        ISignalize("Entities" , FEntityArray.data() , FWidth * FHeight * sizeof(decltype(FEntityArray)::value_type));
    }

    void ISignalizeMovement(NSpace::SSelection const& ASelection)
    {
        ISignalize("Movement" , &ASelection , sizeof(ASelection));
    }

    void IReact()
    {
        std::int64_t LSignal;
        NNetwork::IReceiveIntegral(LSignal);
        FReactionArray[LSignal]();
        NNetwork::FAddressee = NNetwork::FClientArray[(NNetwork::FAddressee + 1) % std::ssize(NNetwork::FClientArray)];
    }

    void IReactDimensions()
    {
        ISignalizeDimensions();
    }

    void IReactTerrains()
    {
        ISignalizeTerrains();
    }

    void IReactEntities()
    {
        ISignalizeEntities();
    }

    void IReactMovement()
    {
        struct SMovement
        {
            std::int64_t FSelectionX;
            std::int64_t FSelectionY;
            std::int64_t FOrderX;
            std::int64_t FOrderY;
        }
        LMovement;
        NNetwork::IReceive(&LMovement , sizeof(LMovement));
        if(FEntityArray[LMovement.FSelectionY * FWidth + LMovement.FSelectionX].IName() != "/_.png")
        {
            FOrderArray.emplace_back(LMovement.FSelectionX , LMovement.FSelectionY , LMovement.FOrderX , LMovement.FOrderY , 1'000.0);
        }
    }

    void IReactEntity()
    {
        struct SEntity
        {
            std::int64_t FX;
            std::int64_t FY;
            std::int64_t FCode;
        }
        LEntity;
        NNetwork::IReceive(&LEntity , sizeof(LEntity));
        FEntityArray[LEntity.FY * FWidth + LEntity.FX].FCode = LEntity.FCode; 
    }
}