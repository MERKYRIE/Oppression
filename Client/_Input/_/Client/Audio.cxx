#include"Client.hxx"

namespace NOppression::NClient
{
    SAudio::SAudio()
    {
        /*
        GDebug.IMask(Mix_Init(MIX_INIT_MP3));
        GDebug.ICode(Mix_OpenAudioDevice(MIX_DEFAULT_FREQUENCY , MIX_DEFAULT_FORMAT , MIX_DEFAULT_CHANNELS , 2048 , nullptr , 0));
        std::int32_t LFrequency;
        std::uint16_t LFormat;
        std::int32_t LChannels;
        GDebug.IAssert(!Mix_QuerySpec(&LFrequency , &LFormat , &LChannels));
        GDebug.IAssert(LFrequency != MIX_DEFAULT_FREQUENCY || LFormat != MIX_DEFAULT_FORMAT || LChannels != MIX_DEFAULT_CHANNELS);
        GDebug.IAssert(Mix_AllocateChannels(0));
        for(std::filesystem::directory_entry const& LEntry : std::filesystem::recursive_directory_iterator{"Sounds"})
        {
            if(LEntry.path().extension() == ".wav")
            {
                FSounds.emplace_back(LEntry.path().generic_string());
            }
        }
        FSounds.shrink_to_fit();
        for(std::filesystem::directory_entry const& LEntry : std::filesystem::recursive_directory_iterator{"Tracks"})
        {
            if(LEntry.path().extension() == ".mp3")
            {
                FTracks.emplace_back(LEntry.path().generic_string());
            }
        }
        FTracks.shrink_to_fit();
        */
    }

    NAudio::STrack& SAudio::ITrack(std::string const& APath)
    {
        return(*std::ranges::find_if(FTracks , [&](NAudio::STrack const& ATrack)->bool{return(ATrack.FPath == APath);}));
    }

    NAudio::SSound& SAudio::ISound(std::string const& APath)
    {
        return(*std::ranges::find_if(FSounds , [&](NAudio::SSound const& ASound)->bool{return(ASound.FPath == APath);}));
    }

    SAudio::~SAudio()
    {
        FTracks.clear();
        FSounds.clear();
        Mix_CloseAudio();
        Mix_Quit();
    }
}