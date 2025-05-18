#pragma comment(lib , "../SimpleDirectMediaLayer/SDL2main")
#pragma comment(lib , "../SimpleDirectMediaLayer/SDL2")
#pragma comment(lib , "../SimpleDirectMediaLayer/Network/SDL2_net")

#include"Server.hxx"

namespace NOppression
{
    SServer::SServer()
    {
        NServer::GDebug.ICode(SDL_Init(SDL_INIT_EVERYTHING));
    }
    
    void SServer::IInitiate()
    {
        while(true)
        {
            NServer::GTime.IUpdate();
            NServer::GSpace.IUpdate();
        }
    }

    SServer::~SServer()
    {
        SDL_Quit();
    }
}

std::int32_t main(std::int32_t , char**)
{
    NOppression::GServer.IInitiate();
    return(0);
}