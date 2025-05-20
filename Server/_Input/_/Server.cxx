#pragma comment(lib , "../SimpleDirectMediaLayer/SDL2main")
#pragma comment(lib , "../SimpleDirectMediaLayer/SDL2")
#pragma comment(lib , "../SimpleDirectMediaLayer/Network/SDL2_net")

#include"Server.hxx"

namespace NOppression::NServer
{
    void IInitialize()
    {
        NDebug::ICode(SDL_Init(SDL_INIT_EVERYTHING));
        NTime::IInitialize();
        NNetwork::IInitialize();
        NSpace::IInitialize();
    }
    
    void IUpdate()
    {
        while(true)
        {
            NTime::IUpdate();
            NNetwork::IUpdate();
            if(NNetwork::FClientArray.empty())
            {
                break;
            }
            NSpace::IUpdate();
        }
    }

    void IDeinitialize()
    {
        NSpace::IDeinitialize();
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