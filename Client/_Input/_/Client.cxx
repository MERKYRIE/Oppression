#pragma comment(lib , "../SimpleDirectMediaLayer/SDL2main")
#pragma comment(lib , "../SimpleDirectMediaLayer/SDL2")
#pragma comment(lib , "../SimpleDirectMediaLayer/Image/SDL2_image")
#pragma comment(lib , "../SimpleDirectMediaLayer/Mixer/SDL2_mixer")
#pragma comment(lib , "../SimpleDirectMediaLayer/Network/SDL2_net")
#pragma comment(lib , "../SimpleDirectMediaLayer/TrueTypeFont/SDL2_ttf")

#include"Client.hxx"

namespace NOppression
{
    SClient::SClient()
    {
        NClient::GDebug.ICode(SDL_Init(SDL_INIT_EVERYTHING));
    }
    
    void SClient::IInitiate()
    {
        while(NClient::GKeyboard.FKeys["Escape"]->FState == "Up")
        {
            NClient::GKeyboard.IUpdate();
            NClient::GMouse.IUpdate();
            NClient::GTime.IUpdate();
            NClient::GSpace.IUpdate();
            NClient::GVideo.IUpdate();
        };
    }

    SClient::~SClient()
    {
        SDL_Quit();
    }
}

std::int32_t main(std::int32_t , char**)
{
    NOppression::GClient.IInitiate();
    return(0);
}