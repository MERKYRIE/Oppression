#pragma once

#include<algorithm>
#include<array>

#include<filesystem>
#include<fstream>
#include<functional>

#include<iostream>

#include<numbers>

#include<random>

#include<source_location>
#include<string>

#include<unordered_map>

#include<variant>
#include<vector>

#pragma warning(push)
    #pragma warning(disable : 26819)

    #include"../SimpleDirectMediaLayer/SDL.h"
    #include"../SimpleDirectMediaLayer/Network/SDL_net.h"
#pragma warning(pop)

namespace NOppression
{
    namespace NServer
    {
        void IInitialize();
        void IUpdate();
        void IDeinitialize();
        
        namespace NDebug
        {
        
        }
        
        namespace NNetwork
        {
            namespace NClient
            {
                struct SClient;
            }
        }
        
        namespace NSpace
        {
            struct SSpace;
            
            namespace NDimensionality
            {
                struct SDimensionality;
            }

            namespace NEntity
            {
                struct SEntity;
            }

            namespace NOrder
            {
                struct SOrder;
            }

            namespace NSelection
            {
                struct SSelection;
            }

            namespace NTerrain
            {
                struct STerrain;
            }
        }

        namespace NTime
        {
        
        }
    }
}