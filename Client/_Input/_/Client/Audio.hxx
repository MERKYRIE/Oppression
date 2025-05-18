#pragma once

namespace NOppression::NClient
{
    inline struct SAudio
    {
        std::vector<NAudio::SSound> FSounds;
        std::vector<NAudio::STrack> FTracks;

        SAudio();
        NAudio::STrack& ITrack(std::string const& APath);
        NAudio::SSound& ISound(std::string const& APath);
        ~SAudio();
    }
    GAudio;
}