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
            GSpace.GCode = 0 ; auto const& LName : std::initializer_list<std::string>
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
            GSpace.GSignalNameToCodeArray[LName] = GSpace.GCode++;
        }
        for
        (
            GSpace.GCode = 0 ; auto const& LAction : std::initializer_list<std::function<void(SSpace *const&)>>
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
            GSpace.GReactionCodeToActionArray[GSpace.GCode++] = std::bind(LAction , &GSpace);
        }
        GSpace.GWidth = 40;
        GSpace.GHeight = 60;
        for(GSpace.GCode = 0 ; auto const& LEntry : std::filesystem::recursive_directory_iterator{"Images/Terrains"})
        {
            if(LEntry.path().extension() == ".png")
            {
                GSpace.GTerrainNameToCodeArray[LEntry.path().generic_string().substr(LEntry.path().generic_string().find('/' , LEntry.path().generic_string().find('/') + 1))] = GSpace.GCode++;
            }
        }
        NTerrain::IInitialize();
        GSpace.GTerrainCodeArray.resize(GSpace.GWidth * GSpace.GHeight);
        {
            GSpace.GFile.open("Terrains/Antifreeze.txt" , std::ios::in);
            for(auto & LTerrain : GSpace.GTerrainCodeArray)
            {
                GSpace.GFile >> NTerrain::GName;
                NTerrain::IConstruct();
                LTerrain = NTerrain::GTerrain;
            }
        }
        GSpace.GTerrainArray.resize(GSpace.GWidth * GSpace.GHeight);
        for(GSpace.GCode = 0 ; auto const& LEntry : std::filesystem::recursive_directory_iterator{"Images/Entities"})
        {
            if(LEntry.path().extension() == ".png")
            {
                GSpace.GEntityNameToCodeArray[LEntry.path().generic_string().substr(LEntry.path().generic_string().find('/' , LEntry.path().generic_string().find('/') + 1))] = GSpace.GCode++;
            }
        }
        NEntity::IInitialize();
        GSpace.GEntityCodeArray.resize(GSpace.GWidth * GSpace.GHeight);
        GSpace.GEntityArray.resize(GSpace.GWidth * GSpace.GHeight);
        NEntity::GName = "/_.png";
        for(auto & LEntity : GSpace.GEntityCodeArray)
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
        for(auto const& LOrder : GSpace.GOrderCodeArray)
        {
            NOrder::GOrder = LOrder;
            NOrder::IUpdate();
        }
        do
        {
            GSpace.GIsRemoved = false;
            for(auto LOrder{GSpace.GOrderCodeArray.begin()} ; LOrder != GSpace.GOrderCodeArray.end() ; LOrder++)
            {
                NOrder::GOrder = *LOrder;
                NOrder::IIsCompleted();
                if(NOrder::GIsCompleted)
                {
                    GSpace.GOrderCodeArray.erase(LOrder);
                    GSpace.GIsRemoved = true;
                    break;
                }
            }
        }
        while(GSpace.GIsRemoved);
    }

    void SSpace::ISignalize()
    {
        GSpace.GByteArray.resize(sizeof(decltype(GSpace.GSignalNameToCodeArray)::mapped_type) + GSpace.GSize);
        std::memcpy(&GSpace.GByteArray[0] , &GSpace.GSignalNameToCodeArray[GSpace.GName] , sizeof(decltype(GSpace.GSignalNameToCodeArray)::mapped_type));
        if(GSpace.GData && GSpace.GSize)
        {
            std::memcpy(&GSpace.GByteArray[sizeof(decltype(GSpace.GSignalNameToCodeArray)::mapped_type)] , GSpace.GData , GSpace.GSize);
        }
        NNetwork::GData = GSpace.GByteArray.data();
        NNetwork::GSize = std::ssize(GSpace.GByteArray);
        NNetwork::ISend();
    }

    void SSpace::ISignalizeDimensionality()
    {
        NDimensionality::GX = GSpace.GWidth;
        NDimensionality::GY = GSpace.GHeight;
        NDimensionality::IConstruct();
        GSpace.GName = "Dimensionality";
        GSpace.GData = NDimensionality::GDimensionalityArray[NDimensionality::GDimensionality];
        GSpace.GSize = sizeof(std::remove_pointer_t<decltype(NDimensionality::GDimensionalityArray)::mapped_type>);
        ISignalize();
        NDimensionality::IDeconstruct();
    }

    void SSpace::ISignalizeTerrainArray()
    {
        for(std::int64_t LTerrainArrayIndex{0} ; auto & LTerrain : GSpace.GTerrainArray)
        {
            LTerrain = *NTerrain::GTerrainArray[GSpace.GTerrainCodeArray[LTerrainArrayIndex++]];
        }
        GSpace.GName = "TerrainArray";
        GSpace.GData = GSpace.GTerrainArray.data();
        GSpace.GSize = GSpace.GWidth * GSpace.GHeight * sizeof(decltype(GSpace.GTerrainArray)::value_type);
        ISignalize();
    }

    void SSpace::ISignalizeEntityArray()
    {
        for(std::int64_t LEntityArrayIndex{0} ; auto & LEntity : GSpace.GEntityArray)
        {
            LEntity = *NEntity::GEntityArray[GSpace.GEntityCodeArray[LEntityArrayIndex++]];
        }
        GSpace.GName = "EntityArray";
        GSpace.GData = GSpace.GEntityArray.data();
        GSpace.GSize = GSpace.GWidth * GSpace.GHeight * sizeof(decltype(GSpace.GEntityArray)::value_type);
        ISignalize();
    }

    void SSpace::ISignalizeSelection()
    {
        GSpace.GName = "Selection";
        GSpace.GData = NSelection::GSelectionArray[GSpace.GSelection];
        GSpace.GSize = sizeof(std::remove_pointer_t<decltype(NSelection::GSelectionArray)::mapped_type>);
        ISignalize();
    }

    void SSpace::IReact()
    {
        NNetwork::IReceiveIntegral();
        GSpace.GReactionCodeToActionArray[NNetwork::GIntegral]();
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
        NNetwork::GSize = sizeof(LOrder);
        NNetwork::IReceive();
        NEntity::GEntity = GSpace.GEntityCodeArray[LOrder.FFromY * GSpace.GWidth + LOrder.FFromX];
        NEntity::IName();
        if(NEntity::GName != "/_.png")
        {
            NOrder::GFromX = LOrder.FFromX;
            NOrder::GFromY = LOrder.FFromY;
            NOrder::GToX = LOrder.FToX;
            NOrder::GToY = LOrder.FToY;
            NOrder::GDuration = 1'000.0;
            NOrder::IConstruct();
            GSpace.GOrderCodeArray.emplace_back(NOrder::GOrder);
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
        NNetwork::GSize = sizeof(LEntity);
        NNetwork::IReceive();
        NEntity::GEntityArray[GSpace.GEntityCodeArray[LEntity.FY * GSpace.GWidth + LEntity.FX]]->FCode = LEntity.FCode; 
    }

    void SSpace::IDeinitialize()
    {
        for(auto const& LOrder : GSpace.GOrderCodeArray)
        {
            NOrder::GOrder = LOrder;
            NOrder::IDeconstruct();
        }
        GSpace.GOrderCodeArray.clear();
        NOrder::IDeinitialize();
        NSelection::IDeinitialize();
        NDimensionality::IDeinitialize();
        for(auto const& LEntity : GSpace.GEntityCodeArray)
        {
            NEntity::GEntity = LEntity;
            NEntity::IDeconstruct();
        }
        GSpace.GEntityCodeArray.clear();
        NEntity::IDeinitialize();
        for(auto const& LTerrain : GSpace.GTerrainCodeArray)
        {
            NTerrain::GTerrain = LTerrain;
            NTerrain::IDeconstruct();
        }
        GSpace.GTerrainCodeArray.clear();
        NTerrain::IDeinitialize();
    }
}