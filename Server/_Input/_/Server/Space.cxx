#include"Server.hxx"
#include"Space.hxx"

#include"Network.hxx"

#include"Space/Dimensionality.hxx"
#include"Space/Entity.hxx"
#include"Space/Order.hxx"
#include"Space/Selection.hxx"
#include"Space/Terrain.hxx"

namespace NOppression::NServer::NSpace
{
    SSpace GSpace;

    void SSpace::IInitialize()
    {
        for
        (
            FCode = 0 ; auto const& LSignalType : std::initializer_list<std::reference_wrapper<std::int64_t>>
            {
                FSignalType.FDimensionality
                ,
                FSignalType.FTerrainArray
                ,
                FSignalType.FEntityArray
                ,
                FSignalType.FSelection
            }
        )
        {
            LSignalType.get() = FCode++;
        }
        for
        (
            FCode = 0 ; auto const& LAction : std::initializer_list<std::function<void(SSpace *const&)>>
            {
                &SSpace::IReactDimensionality
                ,
                &SSpace::IReactTerrainArray
                ,
                &SSpace::IReactEntitieArray
                ,
                &SSpace::IReactOrder
                ,
                &SSpace::IReactEntity
            }
        )
        {
            FReactionCodeToActionArray[FCode++] = std::bind(LAction , this);
        }
        FWidth = 40;
        FHeight = 60;
        for(FCode = 0 ; auto const& LEntry : std::filesystem::recursive_directory_iterator{"Images/Terrains"})
        {
            if(LEntry.path().extension() == ".png")
            {
                FTerrainNameToCodeArray[LEntry.path().generic_string().substr(LEntry.path().generic_string().find('/' , LEntry.path().generic_string().find('/') + 1))] = FCode++;
            }
        }
        NTerrain::IInitialize();
        FTerrainCodeArray.resize(FWidth * FHeight);
        FFile.open("Terrains/Antifreeze.txt" , std::ios::in);
        for(auto & LTerrain : FTerrainCodeArray)
        {
            FFile >> NTerrain::GName;
            NTerrain::IConstruct();
            LTerrain = NTerrain::GTerrain;
        }
        FFile.close();
        FTerrainArray.resize(FWidth * FHeight);
        for(FCode = 0 ; auto const& LEntry : std::filesystem::recursive_directory_iterator{"Images/Entities"})
        {
            if(LEntry.path().extension() == ".png")
            {
                FEntityNameToCodeArray[LEntry.path().generic_string().substr(LEntry.path().generic_string().find('/' , LEntry.path().generic_string().find('/') + 1))] = FCode++;
            }
        }
        NEntity::IInitialize();
        FEntityCodeArray.resize(FWidth * FHeight);
        FEntityArray.resize(FWidth * FHeight);
        NEntity::GName = "/_.png";
        for(auto & LEntity : FEntityCodeArray)
        {
            NEntity::IConstruct();
            LEntity = NEntity::GEntity;
        }
        NDimensionality::IInitialize();
        NSelection::IInitialize();
        NOrder::IInitialize();
    }

    void SSpace::IUpdate()
    {
        IReact();
        for(auto const& LOrder : FOrderCodeArray)
        {
            NOrder::GOrder = LOrder;
            NOrder::IUpdate();
        }
        do
        {
            FIsRemoved = false;
            for(auto LOrder{FOrderCodeArray.begin()} ; LOrder != FOrderCodeArray.end() ; LOrder++)
            {
                NOrder::GOrder = *LOrder;
                NOrder::IIsCompleted();
                if(NOrder::GIsCompleted)
                {
                    FOrderCodeArray.erase(LOrder);
                    FIsRemoved = true;
                    break;
                }
            }
        }
        while(FIsRemoved);
    }

    void SSpace::ISignalize()
    {
        FByteArray.resize(sizeof(decltype(FSignal)) + FSize);
        std::memcpy(&FByteArray[0] , &FSignal , sizeof(decltype(FSignal)));
        if(FData && FSize)
        {
            std::memcpy(&FByteArray[sizeof(decltype(FSignal))] , FData , FSize);
        }
        NNetwork::GData = FByteArray.data();
        NNetwork::GSize = std::ssize(FByteArray);
        NNetwork::ISend();
    }

    void SSpace::ISignalizeDimensionality()
    {
        NDimensionality::GX = FWidth;
        NDimensionality::GY = FHeight;
        NDimensionality::IConstruct();
        FSignal = FSignalType.FDimensionality;
        FData = NDimensionality::GDimensionalityArray[NDimensionality::GDimensionality];
        FSize = sizeof(std::remove_pointer_t<decltype(NDimensionality::GDimensionalityArray)::mapped_type>);
        ISignalize();
        NDimensionality::IDeconstruct();
    }

    void SSpace::ISignalizeTerrainArray()
    {
        for(std::int64_t LTerrainArrayIndex{0} ; auto & LTerrain : FTerrainArray)
        {
            LTerrain = *NTerrain::GTerrainArray[FTerrainCodeArray[LTerrainArrayIndex++]];
        }
        FSignal = FSignalType.FTerrainArray;
        FData = FTerrainArray.data();
        FSize = FWidth * FHeight * sizeof(decltype(FTerrainArray)::value_type);
        ISignalize();
    }

    void SSpace::ISignalizeEntityArray()
    {
        for(std::int64_t LEntityArrayIndex{0} ; auto & LEntity : FEntityArray)
        {
            LEntity = *NEntity::GEntityArray[FEntityCodeArray[LEntityArrayIndex++]];
        }
        FSignal = FSignalType.FEntityArray;
        FData = FEntityArray.data();
        FSize = FWidth * FHeight * sizeof(decltype(FEntityArray)::value_type);
        ISignalize();
    }

    void SSpace::ISignalizeSelection()
    {
        FSignal = FSignalType.FSelection;
        FData = NSelection::GSelectionArray[FSelection];
        FSize = sizeof(std::remove_pointer_t<decltype(NSelection::GSelectionArray)::mapped_type>);
        ISignalize();
    }

    void SSpace::IReact()
    {
        NNetwork::IReceiveIntegral();
        FReactionCodeToActionArray[NNetwork::GIntegral]();
    }

    void SSpace::IReactDimensionality()
    {
        ISignalizeDimensionality();
    }

    void SSpace::IReactTerrainArray()
    {
        ISignalizeTerrainArray();
    }

    void SSpace::IReactEntitieArray()
    {
        ISignalizeEntityArray();
    }

    void SSpace::IReactOrder()
    {
        struct SOrder
        {
            std::int64_t FFromX;
            std::int64_t FFromY;
            std::int64_t FToX;
            std::int64_t FToY;
        }
        LOrder;
        NNetwork::GData = &LOrder;
        NNetwork::GSize = sizeof(decltype(LOrder));
        NNetwork::IReceive();
        NEntity::GEntity = FEntityCodeArray[LOrder.FFromY * FWidth + LOrder.FFromX];
        NEntity::IName();
        if(NEntity::GName != "/_.png")
        {
            NOrder::GFromX = LOrder.FFromX;
            NOrder::GFromY = LOrder.FFromY;
            NOrder::GToX = LOrder.FToX;
            NOrder::GToY = LOrder.FToY;
            NOrder::GDuration = 1'000.0;
            NOrder::IConstruct();
            FOrderCodeArray.emplace_back(NOrder::GOrder);
        }
    }

    void SSpace::IReactEntity()
    {
        struct SEntity
        {
            std::int64_t FX;
            std::int64_t FY;
            std::int64_t FCode;
        }
        LEntity;
        NNetwork::GData = &LEntity;
        NNetwork::GSize = sizeof(decltype(LEntity));
        NNetwork::IReceive();
        NEntity::GEntityArray[FEntityCodeArray[LEntity.FY * FWidth + LEntity.FX]]->FCode = LEntity.FCode; 
    }

    void SSpace::IDeinitialize()
    {
        for(auto const& LOrder : FOrderCodeArray)
        {
            NOrder::GOrder = LOrder;
            NOrder::IDeconstruct();
        }
        FOrderCodeArray.clear();
        NOrder::IDeinitialize();
        NSelection::IDeinitialize();
        NDimensionality::IDeinitialize();
        for(auto const& LEntity : FEntityCodeArray)
        {
            NEntity::GEntity = LEntity;
            NEntity::IDeconstruct();
        }
        FEntityCodeArray.clear();
        NEntity::IDeinitialize();
        for(auto const& LTerrain : FTerrainCodeArray)
        {
            NTerrain::GTerrain = LTerrain;
            NTerrain::IDeconstruct();
        }
        FTerrainCodeArray.clear();
        NTerrain::IDeinitialize();
    }
}