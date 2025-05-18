#include"Client.hxx"

namespace NOppression::NClient::NAudio
{
    SSound::SSound(std::string const& APath)
    {
        FPath = APath.substr(APath.find('/'));
        GDebug.IHandle(FHandle = Mix_LoadWAV(APath.c_str()));
        FChannel = Mix_AllocateChannels(SDL_QUERY);
        GDebug.IAssert(Mix_AllocateChannels(Mix_AllocateChannels(SDL_QUERY) + 1) != FChannel + 1);
    }

    void SSound::IPlay()
    {
        Mix_PlayChannel(static_cast<std::int32_t>(FChannel) , FHandle , 0);
    }

    bool SSound::IState()
    {
        return(Mix_Playing(static_cast<std::int32_t>(FChannel)));
    }

    SSound::~SSound()
    {
        Mix_FreeChunk(FHandle);
    }
}