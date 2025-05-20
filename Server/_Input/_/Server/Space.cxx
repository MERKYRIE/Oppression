#include"Server.hxx"

namespace NOppression::NServer::NSpace
{
    void IInitialize()
    {
        for
        (
            GCode = 0 ; auto const& LName : std::initializer_list<std::string>
            {
                "Dimensionality"
                ,
                "TerrainArray"
                ,
                "EntityArray"
                ,
                "Selection"
            }
        )
        {
            GSignalNameToCodeArray[LName] = GCode++;
        }
        for
        (
            GCode = 0 ; auto const& LAction : std::initializer_list<std::function<void()>>
            {
                &IReactDimensionality
                ,
                &IReactTerrainArray
                ,
                &IReactEntitieArray
                ,
                &IReactOrder
                ,
                &IReactEntity
            }
        )
        {
            GReactionCodeToActionArray[GCode++] = std::bind(LAction);
        }
        GWidth = 40;
        GHeight = 60;
        for(GCode = 0 ; auto const& LEntry : std::filesystem::recursive_directory_iterator{"Images/Terrains"})
        {
            if(LEntry.path().extension() == ".png")
            {
                GTerrainNameToCodeArray[LEntry.path().generic_string().substr(LEntry.path().generic_string().find('/' , LEntry.path().generic_string().find('/') + 1))] = GCode++;
            }
        }
        NTerrain::IInitialize();
        GTerrainCodeArray.resize(GWidth * GHeight);
        {
            GFile.open("Terrains/Antifreeze.txt" , std::ios::in);
            for(auto & LTerrain : GTerrainCodeArray)
            {
                GFile >> NTerrain::GName;
                NTerrain::IConstruct();
                LTerrain = NTerrain::GTerrain;
            }
        }
        GTerrainArray.resize(GWidth * GHeight);
        for(GCode = 0 ; auto const& LEntry : std::filesystem::recursive_directory_iterator{"Images/Entities"})
        {
            if(LEntry.path().extension() == ".png")
            {
                GEntityNameToCodeArray[LEntry.path().generic_string().substr(LEntry.path().generic_string().find('/' , LEntry.path().generic_string().find('/') + 1))] = GCode++;
            }
        }
        NEntity::IInitialize();
        GEntityCodeArray.resize(GWidth * GHeight);
        GEntityArray.resize(GWidth * GHeight);
        NEntity::GName = "/_.png";
        for(auto & LEntity : GEntityCodeArray)
        {
            NEntity::IConstruct();
            LEntity = NEntity::GEntity;
        }
        NDimensionality::IInitialize();
        NSelection::IInitialize();
        NOrder::IInitialize();
    }

    void IUpdate()
    {
        IReact();
        for(auto const& LOrder : GOrderCodeArray)
        {
            NOrder::GOrder = LOrder;
            NOrder::IUpdate();
        }
        do
        {
            GIsRemoved = false;
            for(auto LOrder{GOrderCodeArray.begin()} ; LOrder != GOrderCodeArray.end() ; LOrder++)
            {
                NOrder::GOrder = *LOrder;
                NOrder::IIsCompleted();
                if(NOrder::GIsCompleted)
                {
                    GOrderCodeArray.erase(LOrder);
                    GIsRemoved = true;
                    break;
                }
            }
        }
        while(GIsRemoved);
    }

    void ISignalize()
    {
        GByteArray.resize(sizeof(decltype(GSignalNameToCodeArray)::mapped_type) + GSize);
        std::memcpy(&GByteArray[0] , &GSignalNameToCodeArray[GName] , sizeof(decltype(GSignalNameToCodeArray)::mapped_type));
        if(GData && GSize)
        {
            std::memcpy(&GByteArray[sizeof(decltype(GSignalNameToCodeArray)::mapped_type)] , GData , GSize);
        }
        NNetwork::GData = GByteArray.data();
        NNetwork::GSize = std::ssize(GByteArray);
        NNetwork::ISend();
    }

    void ISignalizeDimensionality()
    {
        NDimensionality::GX = GWidth;
        NDimensionality::GY = GHeight;
        NDimensionality::IConstruct();
        GName = "Dimensionality";
        GData = NDimensionality::GDimensionalityArray[NDimensionality::GDimensionality];
        GSize = sizeof(std::remove_pointer_t<decltype(NDimensionality::GDimensionalityArray)::mapped_type>);
        ISignalize();
        NDimensionality::IDeconstruct();
    }

    void ISignalizeTerrainArray()
    {
        for(std::int64_t LTerrainArrayIndex{0} ; auto & LTerrain : GTerrainArray)
        {
            LTerrain = *NTerrain::GTerrainArray[GTerrainCodeArray[LTerrainArrayIndex++]];
        }
        GName = "TerrainArray";
        GData = GTerrainArray.data();
        GSize = GWidth * GHeight * sizeof(decltype(GTerrainArray)::value_type);
        ISignalize();
    }

    void ISignalizeEntityArray()
    {
        for(std::int64_t LEntityArrayIndex{0} ; auto & LEntity : GEntityArray)
        {
            LEntity = *NEntity::GEntityArray[GEntityCodeArray[LEntityArrayIndex++]];
        }
        GName = "EntityArray";
        GData = GEntityArray.data();
        GSize = GWidth * GHeight * sizeof(decltype(GEntityArray)::value_type);
        ISignalize();
    }

    void ISignalizeSelection()
    {
        GName = "Selection";
        GData = NSelection::GSelectionArray[GSelection];
        GSize = sizeof(std::remove_pointer_t<decltype(NSelection::GSelectionArray)::mapped_type>);
        ISignalize();
    }

    void IReact()
    {
        NNetwork::IReceiveIntegral();
        GReactionCodeToActionArray[NNetwork::GIntegral]();
    }

    void IReactDimensionality()
    {
        ISignalizeDimensionality();
    }

    void IReactTerrainArray()
    {
        ISignalizeTerrainArray();
    }

    void IReactEntitieArray()
    {
        ISignalizeEntityArray();
    }

    void IReactOrder()
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
        NNetwork::GSize = sizeof(LOrder);
        NNetwork::IReceive();
        NEntity::GEntity = GEntityCodeArray[LOrder.FFromY * GWidth + LOrder.FFromX];
        NEntity::IName();
        if(NEntity::GName != "/_.png")
        {
            NOrder::GFromX = LOrder.FFromX;
            NOrder::GFromY = LOrder.FFromY;
            NOrder::GToX = LOrder.FToX;
            NOrder::GToY = LOrder.FToY;
            NOrder::GDuration = 1'000.0;
            NOrder::IConstruct();
            GOrderCodeArray.emplace_back(NOrder::GOrder);
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
        NNetwork::GData = &LEntity;
        NNetwork::GSize = sizeof(LEntity);
        NNetwork::IReceive();
        NEntity::GEntityArray[GEntityCodeArray[LEntity.FY * GWidth + LEntity.FX]]->FCode = LEntity.FCode; 
    }

    void IDeinitialize()
    {
        for(auto const& LOrder : GOrderCodeArray)
        {
            NOrder::GOrder = LOrder;
            NOrder::IDeconstruct();
        }
        GOrderCodeArray.clear();
        NOrder::IDeinitialize();
        NSelection::IDeinitialize();
        NDimensionality::IDeinitialize();
        for(auto const& LEntity : GEntityCodeArray)
        {
            NEntity::GEntity = LEntity;
            NEntity::IDeconstruct();
        }
        GEntityCodeArray.clear();
        NEntity::IDeinitialize();
        for(auto const& LTerrain : GTerrainCodeArray)
        {
            NTerrain::GTerrain = LTerrain;
            NTerrain::IDeconstruct();
        }
        GTerrainCodeArray.clear();
        NTerrain::IDeinitialize();
    }
}