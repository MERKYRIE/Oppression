#pragma once

#include<array>

#include<filesystem>
#include<fstream>
#include<functional>

#include<iostream>

#include<numbers>

#include<random>

#include<source_location>
#include<string>

#include<unordered_map>

#include<variant>
#include<vector>

#pragma warning(push)
    #pragma warning(disable : 26819)

    #include"../SimpleDirectMediaLayer/SDL.h"
    #include"../SimpleDirectMediaLayer/Image/SDL_image.h"
    #include"../SimpleDirectMediaLayer/Mixer/SDL_mixer.h"
    #include"../SimpleDirectMediaLayer/Network/SDL_net.h"
    #include"../SimpleDirectMediaLayer/TrueTypeFont/SDL_ttf.h"
#pragma warning(pop)

namespace NOppression
{
    inline struct SClient
    {
        SClient();
        void IInitiate();
        ~SClient();
    }
    GClient;

    namespace NClient
    {
        namespace NAudio
        {
            struct SSound;
            struct STrack;
        }
        
        namespace NKeyboard
        {
            struct SKey;
        }
            
        namespace NMouse
        {
            struct SAbsolute;
            struct SButton;
            struct SCursor;
            struct SPixel;
            struct SRectangle;
            struct SRelative;
            struct SSquare;
            struct SWheel;
        }

        namespace NSpace
        {
            struct SImage;
        }

        namespace NVideo
        {
            struct SFont;
            struct SImage;
        }
    }
}

#include"Client/Audio/Sound.hxx"
#include"Client/Audio/Track.hxx"

#include"Client/Keyboard/Key.hxx"

#include"Client/Mouse/Absolute.hxx"
#include"Client/Mouse/Button.hxx"
#include"Client/Mouse/Cursor.hxx"
#include"Client/Mouse/Pixel.hxx"
#include"Client/Mouse/Rectangle.hxx"
#include"Client/Mouse/Relative.hxx"
#include"Client/Mouse/Square.hxx"
#include"Client/Mouse/Wheel.hxx"

#include"Client/Space/Image.hxx"

#include"Client/Video/Font.hxx"
#include"Client/Video/Image.hxx"

#include"Client/Debug.hxx"
#include"Client/Time.hxx"
#include"Client/Network.hxx"
#include"Client/Keyboard.hxx"
#include"Client/Mouse.hxx"
#include"Client/Audio.hxx"
#include"Client/Video.hxx"
#include"Client/Space.hxx"
#include"Client/Interface.hxx"