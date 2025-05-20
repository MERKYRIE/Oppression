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
        NTerrain::IInitialize();
        FTerrainArray.resize(FWidth * FHeight);
        {
            std::fstream LStream{"Terrains/Antifreeze.txt" , std::ios::in};
            for(auto & LTerrain : FTerrainArray)
            {
                LStream >> NTerrain::GName;
                NTerrain::IConstruct();
                LTerrain = NTerrain::GTerrain;
            }
        }
        for(std::int64_t LCode{0} ; auto const& LEntry : std::filesystem::recursive_directory_iterator{"Images/Entities"})
        {
            if(LEntry.path().extension() == ".png")
            {
                FEntityAdaptorArray[LEntry.path().generic_string().substr(LEntry.path().generic_string().find('/' , LEntry.path().generic_string().find('/') + 1))] = LCode++;
            }
        }
        NEntity::IInitialize();
        FEntityArray.resize(FWidth * FHeight);
        NEntity::GName = "/_.png";
        for(auto & LEntity : FEntityArray)
        {
            NEntity::IConstruct();
            LEntity = NEntity::GEntity;
        }
    }

    void IUpdate()
    {
        IReact();
        for(auto const& LOrder : FOrderArray)
        {
            NOrder::GOrder = LOrder;
            NOrder::IUpdate();
        }
        bool LRemoved;
        do
        {
            LRemoved = false;
            for(auto LOrder{FOrderArray.begin()} ; LOrder != FOrderArray.end() ; LOrder++)
            {
                NOrder::GOrder = *LOrder;
                NOrder::IIsCompleted();
                if(NOrder::GIsCompleted)
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
        NNetwork::FData = LSignal.data();
        NNetwork::FSize = std::ssize(LSignal);
        NNetwork::ISend();
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
        std::vector<NTerrain::STerrain> LTerrainArray;
        LTerrainArray.resize(FWidth * FHeight);
        for(std::int64_t LTerrainArrayIndex{0} ; auto & LTerrain : LTerrainArray)
        {
            LTerrain = *NTerrain::GTerrainArray[FTerrainArray[LTerrainArrayIndex++]];

        }
        ISignalize("Terrains" , LTerrainArray.data() , FWidth * FHeight * sizeof(decltype(LTerrainArray)::value_type));
    }

    void ISignalizeEntities()
    {
        std::vector<NEntity::SEntity> LEntityArray;
        LEntityArray.resize(FWidth * FHeight);
        for(std::int64_t LEntityArrayIndex{0} ; auto & LEntity : LEntityArray)
        {
            LEntity = *NEntity::GEntityArray[FEntityArray[LEntityArrayIndex++]];
        }
        ISignalize("Entities" , LEntityArray.data() , FWidth * FHeight * sizeof(decltype(LEntityArray)::value_type));
    }

    void ISignalizeMovement(NSpace::SSelection const& ASelection)
    {
        ISignalize("Movement" , &ASelection , sizeof(ASelection));
    }

    void IReact()
    {
        std::int64_t LSignal;
        NNetwork::FIntegral = &LSignal;
        NNetwork::IReceiveIntegral();
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
        NNetwork::FData = &LMovement;
        NNetwork::FSize = sizeof(LMovement);
        NNetwork::IReceive();
        NEntity::GEntity = FEntityArray[LMovement.FSelectionY * FWidth + LMovement.FSelectionX];
        NEntity::IName();
        if(NEntity::GName != "/_.png")
        {
            NOrder::GFromX = LMovement.FSelectionX;
            NOrder::GFromY = LMovement.FSelectionY;
            NOrder::GToX = LMovement.FOrderX;
            NOrder::GToY = LMovement.FOrderY;
            NOrder::GDuration = 1'000.0;
            NOrder::IConstruct();
            FOrderArray.emplace_back(NOrder::GOrder);
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
        NNetwork::FData = &LEntity;
        NNetwork::FSize = sizeof(LEntity);
        NNetwork::IReceive();
        NEntity::GEntityArray[FEntityArray[LEntity.FY * FWidth + LEntity.FX]]->FCode = LEntity.FCode; 
    }

    void IDeinitialize()
    {
        for(auto const& LTerrain : FTerrainArray)
        {
            NTerrain::GTerrain = LTerrain;
            NTerrain::IDeconstruct();
        }
        FTerrainArray.clear();
        NTerrain::IDeinitialize();
        for(auto const& LEntity : FEntityArray)
        {
            NEntity::GEntity = LEntity;
            NEntity::IDeconstruct();
        }
        FEntityArray.clear();
        NEntity::IDeinitialize();
    }
}