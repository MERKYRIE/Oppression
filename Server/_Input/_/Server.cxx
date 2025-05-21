#pragma comment(lib , "../SimpleDirectMediaLayer/SDL2main")
#pragma comment(lib , "../SimpleDirectMediaLayer/SDL2")
#pragma comment(lib , "../SimpleDirectMediaLayer/Network/SDL2_net")

#include"Server.hxx"

#include"Server/Debug.hxx"
#include"Server/Network.hxx"
#include"Server/Space.hxx"
#include"Server/Time.hxx"

/*
    Server > Debug
           > Network
           > Space
           > Time

    Network > Debug
            > Client

    Space > Network
          > Dimensionality
          > Entity
          > Order
          > Selection
          > Terrain

    Client > Debug
           > Network

    Entity > Space

    Order > Space
          > Time
          > Entity
          > Selection

    Terrain > Space
*/

namespace NOppression::NServer
{
    void IInitialize()
    {
        NDebug::ICode(SDL_Init(SDL_INIT_EVERYTHING));
        NTime::IInitialize();
        NNetwork::IInitialize();
        NSpace::GSpace.IInitialize();
    }
    
    void IUpdate()
    {
        while(true)
        {
            NTime::IUpdate();
            NNetwork::IUpdate();
            if(NNetwork::GClientArray.empty())
            {
                break;
            }
            NSpace::GSpace.IUpdate();
        }
    }

    void IDeinitialize()
    {
        NSpace::GSpace.IDeinitialize();
        NNetwork::IDeinitialize();
        NTime::IDeinitialize();
        SDL_Quit();
    }
}

std::int32_t main(std::int32_t , char **)
{
    NOppression::NServer::IInitialize();
    NOppression::NServer::IUpdate();
    NOppression::NServer::IDeinitialize();
    return(0);
}