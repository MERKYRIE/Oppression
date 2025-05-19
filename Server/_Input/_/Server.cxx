#pragma comment(lib , "../SimpleDirectMediaLayer/SDL2main")
#pragma comment(lib , "../SimpleDirectMediaLayer/SDL2")
#pragma comment(lib , "../SimpleDirectMediaLayer/Network/SDL2_net")

#include"Server.hxx"

namespace NOppression::NServer
{
    void IInitialize()
    {
        NDebug::ICode(SDL_Init(SDL_INIT_EVERYTHING));
        NNetwork::IInitialize();
        NSpace::IInitialize();
    }
    
    void IExecute()
    {
        IInitialize();
        while(!NNetwork::FClientArray.empty())
        {
            NTime::IUpdate();
            NNetwork::IUpdate();
            NSpace::IUpdate();
        }
        IDeinitialize();
    }

    void IDeinitialize()
    {
        NNetwork::IDeinitialize();
        SDL_Quit();
    }
}

std::int32_t main(std::int32_t , char **)
{
    NOppression::NServer::IExecute();
    return(0);
}