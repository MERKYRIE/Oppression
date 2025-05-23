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
                                                                                                       Keyboard Mouse Audio Video   Keyboard Mouse Audio Video                                                              
                                                                                              ^        ^        ^     ^     ^       ^        ^     ^     ^                                                              
                                                                                              |        |        |     |     |       |        |     |     |                                                              
                                               Button            Keyboard Mouse Audio Video   Linker   Pause-----------------       Gamefeel--------------
                                               ^        ^        ^        ^     ^     ^       ^        ^                            ^
                                               |        |        |        |     |     |       |        |                            |
                   Button              Mouse   Video    Linker   Main------------------       Gameplay-------------------------------
                   ^          ^        ^       ^        ^        ^                            ^
                   |          |        |       |        |        *                            *
             Mouse Video      Linker   Server---        Client---------------------------------
    ^        ^     ^          ^        ^                ^
    |        |     |          |        *                *
    Linker   Launcher         Game-----------------------
    ^              ^          ^
    |              X          |
    Oppression-----------------
    ^
    |
    main

       State    < Key    < Keyboard < Input
    -> State    < Button < Mouse <----
    |  Position < Cursor < Mouse     |
    -> State    < Wheel  < Mouse     |
                           Shortcut <-

    std::int32_t main(std::int32_t , char **)
    {
        NOppression::GOppression = new(NOppression::SOppression);
        delete(NOppression::GOppression);
    }

    SOppression::SOppression()
    {
        std::string LState;
        FLauncher = new(NLauncher::SLauncher{LState});
        delete(FLauncher);
        FLinker = new(NLinker::SLinker);
        if(LState == "Server")
        {

        }
        if(LState == "Client")
        {

        }
        delete(FLinker);
    }

    SLauncher::SLauncher(std::string & AState)
    {
        new(NMouse::SMouse{FMouse});
        new(NVideo::SVideo{FVideo});
        while(true)
        {
            FMouse->IUpdate();
            FVideo->IUpdate();
            FX = FMouse->FX / FVideo->FHeight;
            FY = FMouse->FY / FVideo->FHeight;
            if(FMouse->FButton)
            {
                for(auto & LButton : FVideo->FButtonArray)
                {
                    if(LButton->FX1 <= FX && FX <= LButton->FX2 && LButton->FY1 <= FY && FY <= LButton->FY2)
                    {
                        AState = LButton->FName;
                        delete(FVideo);
                        delete(FMouse);
                        return;
                    }
                }
            }
        }
    }
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