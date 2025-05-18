#include"Client.hxx"

namespace NOppression::NClient
{
    SMouse::SMouse()
    {
        for
        (
            auto const& [LInteger , LString] : std::initializer_list<std::pair<std::int64_t , std::string>>
            {
                {SDL_BUTTON_LEFT , "Left"}
                ,
                {SDL_BUTTON_MIDDLE , "Middle"}
                ,
                {SDL_BUTTON_RIGHT , "Right"}
                ,
                {SDL_BUTTON_X1 , "X1"}
                ,
                {SDL_BUTTON_X2 , "X2"}
            }
        )
        {
            FButtons[LString] = std::make_shared<NMouse::SButton>();
            FButtonsAdaptors[LInteger] = LString;
        }
        FCursor = std::make_shared<NMouse::SCursor>();
        FWheel = std::make_shared<NMouse::SWheel>();
    }

    void SMouse::IUpdate()
    {
        for(auto const& [LName , LButton] : FButtons)
        {
            LButton->IPreupdate();
        }
        FCursor->IPreupdate();
        FWheel->IPreupdate();
        SDL_PumpEvents();
        std::vector<SDL_Event> LEvents{static_cast<std::uint64_t>(SDL_PeepEvents(nullptr , 0 , SDL_GETEVENT , SDL_MOUSEMOTION , SDL_MOUSEWHEEL))};
        SDL_PeepEvents(LEvents.data() , static_cast<std::int32_t>(std::ssize(LEvents)) , SDL_GETEVENT , SDL_MOUSEMOTION , SDL_MOUSEWHEEL);
        for(auto const& AEvent : LEvents)
        {
            switch(AEvent.type)
            {
                case(SDL_MOUSEBUTTONDOWN):
                    FButtons[FButtonsAdaptors[AEvent.button.button]]->IPostupdate(AEvent);
                break;
                case(SDL_MOUSEBUTTONUP):
                    FButtons[FButtonsAdaptors[AEvent.button.button]]->IPostupdate(AEvent);
                break;
                case(SDL_MOUSEMOTION):
                    FCursor->IPostupdate(AEvent.motion);
                    for(auto const& [LName , LButton] : FButtons)
                    {
                        if(LButton->FState == "Down")
                        {
                            LButton->IPostupdate(AEvent);
                        }
                    }
                break;
                case(SDL_MOUSEWHEEL):
                    FWheel->IPostupdate(AEvent.wheel);
                break;
            }
        }
    }
}