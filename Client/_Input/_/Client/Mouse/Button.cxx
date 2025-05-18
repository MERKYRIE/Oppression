#include"Client.hxx"

namespace NOppression::NClient::NMouse
{
    SButton::SButton()
    {
        FModification = false;
        FState = "Up";
        FPressed = std::make_shared<SCursor>();
        FReleased = std::make_shared<SCursor>();
        FHeld = std::make_shared<SCursor>();
    }

    SButton* SButton::IPreupdate()
    {
        FModification = false;
        FPressed->IPreupdate();
        FReleased->IPreupdate();
        FHeld->IPreupdate();
        if(FState == "Pressed")
        {
            FState = "Down";
            return(this);
        }
        if(FState == "Released")
        {
            FState = "Up";
            return(this);
        }
        return(this);
    }
    
    SButton* SButton::IPostupdate(SDL_Event const& AEvent)
    {
        FModification = true;
        switch(AEvent.type)
        {
            case(SDL_MOUSEBUTTONDOWN):
                FState = "Pressed";
                FPressed->IPostupdate(AEvent.motion);
            break;
            case(SDL_MOUSEBUTTONUP):
                FState = "Released";
                FReleased->IPostupdate(AEvent.motion);
            break;
            case(SDL_MOUSEMOTION):
                FHeld->IPostupdate(AEvent.motion);
            break;
        }
        return(this);
    }

    SButton::~SButton()
    {
    
    }
}