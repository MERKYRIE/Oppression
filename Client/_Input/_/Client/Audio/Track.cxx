#include"Client.hxx"

namespace NOppression::NClient::NAudio
{
    STrack::STrack(std::string const& APath)
    {
        FPath = APath.substr(APath.find('/'));
        GDebug.IHandle(FHandle = Mix_LoadMUS(APath.c_str()));
    }

    void STrack::IPlay()
    {
        Mix_PlayMusic(FHandle , 0);
    }

    void STrack::IPause()
    {
        Mix_PauseMusic();
    }

    void STrack::IResume()
    {
        Mix_ResumeMusic();
    }

    void STrack::IStop()
    {
        Mix_HaltMusic();
    }

    void STrack::IVolume(std::int64_t const& ALevel)
    {
        Mix_VolumeMusic(static_cast<std::int32_t>(ALevel));
    }

    STrack::~STrack()
    {
        Mix_FreeMusic(FHandle);
    }
}