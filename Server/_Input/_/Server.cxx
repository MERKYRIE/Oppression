#pragma comment(lib , "../SimpleDirectMediaLayer/SDL2main")
#pragma comment(lib , "../SimpleDirectMediaLayer/SDL2")
#pragma comment(lib , "../SimpleDirectMediaLayer/Network/SDL2_net")

#include"Server.hxx"

#include"Server/Debug.hxx"
#include"Server/Network.hxx"
#include"Server/Space.hxx"
#include"Server/Space/Entity.hxx"
#include"Server/Space/Terrain.hxx"
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

/*
                       Network
                       ^
    Time -> Network -> Space
    ^
    Server
    ^
    main
*/

/*           
    Network  Time Network Network
    ^        ^    ^       ^
    Input -> Intermediate Output
    ^
    Server
    ^
    main
*/

/*           
             Network
             ^
    Network  Time            Network
    ^        ^               ^
    Input -> Intermediate -> Output
    ^
    Server
    ^
    main
*/

/*
    Time Network
    ^    ^
    Server
    ^
    main
*/

/*
    Time -> Network
    ^
    Server
    ^
    main
*/

/*
                   Button        Button
                   ^             ^
                   |             |
             Mouse Video   Mouse Video   Keyboard Mouse Audio Video
             ^     ^       ^     ^       ^        ^     ^     ^
             |     |       |     |       |        |     |     |
    Linker   Launcher      Server-       Client----------------
    ^        ^             ^             ^
    |        |             *             *
    Oppression----------------------------
    ^
    |
    main
*/

namespace NOppression::NServer
{
    SServer * GServer;
    
    SServer::SServer()
    {
        NDebug::ICode(SDL_Init(SDL_INIT_EVERYTHING));
        NTime::IInitialize();
        NNetwork::IInitialize();
        GSpace = new(NSpace::SSpace);
        GSpace->IInitialize();
    }
    
    void SServer::IUpdate()
    {
        while(true)
        {
            NTime::IUpdate();
            NNetwork::IUpdate();
            if(NNetwork::GClientArray.empty())
            {
                break;
            }
            GSpace->IUpdate();
        }
    }

    SServer::~SServer()
    {
        GSpace->IDeinitialize();
        delete(GSpace);
        NNetwork::IDeinitialize();
        NTime::IDeinitialize();
        SDL_Quit();
    }
}

std::int32_t main(std::int32_t , char **)
{
    NOppression::NServer::GServer = new(NOppression::NServer::SServer);
    NOppression::NServer::GServer->IUpdate();
    delete(NOppression::NServer::GServer);
    return(0);
}