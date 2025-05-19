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
        void IExecute();
        void IDeinitialize();
        
        namespace NNetwork
        {
            namespace NClient
            {
                struct SClient;
            }
        }
        
        namespace NSpace
        {
            struct SEntity;
            struct SOrder;
            struct SSelection;
            struct STerrain;
        }
    }
}

#include"Server/Network/Client.hxx"

#include"Server/Space/Entity.hxx"
#include"Server/Space/Order.hxx"
#include"Server/Space/Selection.hxx"
#include"Server/Space/Terrain.hxx"

#include"Server/Debug.hxx"
#include"Server/Network.hxx"
#include"Server/Space.hxx"
#include"Server/Time.hxx"