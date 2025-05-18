#include"Client.hxx"

namespace NOppression::NClient::NKeyboard
{
    SKey::SKey()
    {
        FModification = false;
        FState = "Up";
    }

    void SKey::IPreupdate()
    {
        FModification = false;
        if(FState == "Pressed")
        {
            FState = "Down";
            return;
        }
        if(FState == "Released")
        {
            FState = "Up";
            return;
        }
    }
    
    void SKey::IPostupdate(SDL_KeyboardEvent const& AEvent)
    {
        FModification = true;
        switch(AEvent.type)
        {
            case(SDL_KEYDOWN):
                FState = "Pressed";
            break;
            case(SDL_KEYUP):
                FState = "Released";
            break;
        }
    }

    SKey::~SKey()
    {
    
    }
}