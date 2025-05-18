#include"Client.hxx"

namespace NOppression::NClient
{
    SKeyboard::SKeyboard()
    {
        for
        (
            auto const& [LInteger , LString] : std::initializer_list<std::pair<std::int64_t , std::string>>
            {
                {SDL_SCANCODE_ESCAPE , "Escape"}
                ,
                {SDL_SCANCODE_F1 , "F1"}
                ,
                {SDL_SCANCODE_F2 , "F2"}
                ,
                {SDL_SCANCODE_F3 , "F3"}
                ,
                {SDL_SCANCODE_F4 , "F4"}
                ,
                {SDL_SCANCODE_F5 , "F5"}
                ,
                {SDL_SCANCODE_F6 , "F6"}
                ,
                {SDL_SCANCODE_F7 , "F7"}
                ,
                {SDL_SCANCODE_F8 , "F8"}
                ,
                {SDL_SCANCODE_F9 , "F9"}
                ,
                {SDL_SCANCODE_F10 , "F10"}
                ,
                {SDL_SCANCODE_F11 , "F11"}
                ,
                {SDL_SCANCODE_F12 , "F12"}
                ,
                {SDL_SCANCODE_PRINTSCREEN , "PrintScreen"}
                ,
                {SDL_SCANCODE_SCROLLLOCK , "ScrollLock"}
                ,
                {SDL_SCANCODE_PAUSE , "Pause"}
                ,
                {SDL_SCANCODE_GRAVE , "Grave"}
                ,
                {SDL_SCANCODE_1 , "1"}
                ,
                {SDL_SCANCODE_2 , "2"}
                ,
                {SDL_SCANCODE_3 , "3"}
                ,
                {SDL_SCANCODE_4 , "4"}
                ,
                {SDL_SCANCODE_5 , "5"}
                ,
                {SDL_SCANCODE_6 , "6"}
                ,
                {SDL_SCANCODE_7 , "7"}
                ,
                {SDL_SCANCODE_8 , "8"}
                ,
                {SDL_SCANCODE_9 , "9"}
                ,
                {SDL_SCANCODE_0 , "0"}
                ,
                {SDL_SCANCODE_MINUS , "Minus"}
                ,
                {SDL_SCANCODE_EQUALS , "Equals"}
                ,
                {SDL_SCANCODE_BACKSPACE , "Backspace"}
                ,
                {SDL_SCANCODE_TAB , "Tab"}
                ,
                {SDL_SCANCODE_Q , "Q"}
                ,
                {SDL_SCANCODE_W , "W"}
                ,
                {SDL_SCANCODE_E , "E"}
                ,
                {SDL_SCANCODE_R , "R"}
                ,
                {SDL_SCANCODE_T , "T"}
                ,
                {SDL_SCANCODE_Y , "Y"}
                ,
                {SDL_SCANCODE_U , "U"}
                ,
                {SDL_SCANCODE_I , "I"}
                ,
                {SDL_SCANCODE_O , "O"}
                ,
                {SDL_SCANCODE_P , "P"}
                ,
                {SDL_SCANCODE_LEFTBRACKET , "LeftBracket"}
                ,
                {SDL_SCANCODE_RIGHTBRACKET , "RightBracket"}
                ,
                {SDL_SCANCODE_RETURN , "Return"}
                ,
                {SDL_SCANCODE_CAPSLOCK , "CapsLock"}
                ,
                {SDL_SCANCODE_A , "A"}
                ,
                {SDL_SCANCODE_S , "S"}
                ,
                {SDL_SCANCODE_D , "D"}
                ,
                {SDL_SCANCODE_F , "F"}
                ,
                {SDL_SCANCODE_G , "G"}
                ,
                {SDL_SCANCODE_H , "H"}
                ,
                {SDL_SCANCODE_J , "J"}
                ,
                {SDL_SCANCODE_K , "K"}
                ,
                {SDL_SCANCODE_L , "L"}
                ,
                {SDL_SCANCODE_SEMICOLON , "Semicolon"}
                ,
                {SDL_SCANCODE_APOSTROPHE , "Apostrophe"}
                ,
                {SDL_SCANCODE_LSHIFT , "LShift"}
                ,
                {SDL_SCANCODE_Z , "Z"}
                ,
                {SDL_SCANCODE_X , "X"}
                ,
                {SDL_SCANCODE_C , "C"}
                ,
                {SDL_SCANCODE_V , "V"}
                ,
                {SDL_SCANCODE_B , "B"}
                ,
                {SDL_SCANCODE_N , "N"}
                ,
                {SDL_SCANCODE_M , "M"}
                ,
                {SDL_SCANCODE_COMMA , "Comma"}
                ,
                {SDL_SCANCODE_PERIOD , "Period"}
                ,
                {SDL_SCANCODE_SLASH , "Slash"}
                ,
                {SDL_SCANCODE_BACKSLASH , "Backslash"}
                ,
                {SDL_SCANCODE_RSHIFT , "RShift"}
                ,
                {SDL_SCANCODE_LCTRL , "LCtrl"}
                ,
                {SDL_SCANCODE_LGUI , "LGUI"}
                ,
                {SDL_SCANCODE_LALT , "LAlt"}
                ,
                {SDL_SCANCODE_SPACE , "Space"}
                ,
                {SDL_SCANCODE_RALT , "RAlt"}
                ,
                {SDL_SCANCODE_RGUI , "RGUI"}
                ,
                {SDL_SCANCODE_APPLICATION , "Application"}
                ,
                {SDL_SCANCODE_RCTRL , "RCtrl"}
                ,
                {SDL_SCANCODE_INSERT , "Insert"}
                ,
                {SDL_SCANCODE_HOME , "Home"}
                ,
                {SDL_SCANCODE_PAGEUP , "PageUp"}
                ,
                {SDL_SCANCODE_DELETE , "Delete"}
                ,
                {SDL_SCANCODE_END , "End"}
                ,
                {SDL_SCANCODE_PAGEDOWN , "PageDown"}
                ,
                {SDL_SCANCODE_UP , "Up"}
                ,
                {SDL_SCANCODE_LEFT , "Left"}
                ,
                {SDL_SCANCODE_DOWN , "Down"}
                ,
                {SDL_SCANCODE_RIGHT , "Right"}
                ,
                {SDL_SCANCODE_NUMLOCKCLEAR , "NumLockClear"}
                ,
                {SDL_SCANCODE_KP_DIVIDE , "KPDivide"}
                ,
                {SDL_SCANCODE_KP_MULTIPLY , "KPMultiply"}
                ,
                {SDL_SCANCODE_KP_MINUS , "KPMinus"}
                ,
                {SDL_SCANCODE_KP_7 , "KP7"}
                ,
                {SDL_SCANCODE_KP_8 , "KP8"}
                ,
                {SDL_SCANCODE_KP_9 , "KP9"}
                ,
                {SDL_SCANCODE_KP_PLUS , "KPPlus"}
                ,
                {SDL_SCANCODE_KP_4 , "KP4"}
                ,
                {SDL_SCANCODE_KP_5 , "KP5"}
                ,
                {SDL_SCANCODE_KP_7 , "KP6"}
                ,
                {SDL_SCANCODE_KP_1 , "KP1"}
                ,
                {SDL_SCANCODE_KP_2 , "KP2"}
                ,
                {SDL_SCANCODE_KP_3 , "KP3"}
                ,
                {SDL_SCANCODE_KP_ENTER , "KPEnter"}
                ,
                {SDL_SCANCODE_KP_0 , "KP0"}
                ,
                {SDL_SCANCODE_KP_PERIOD , "KPPeriod"}
            }
        )
        {
            FKeys[LString] = std::make_shared<NKeyboard::SKey>();
            FKeysAdaptors[LInteger] = LString;
        }
    }

    void SKeyboard::IUpdate()
    {
        for(auto const& [LName , LKey] : FKeys)
        {
            LKey->IPreupdate();
        }
        SDL_PumpEvents();
        std::vector<SDL_Event> LEvents{static_cast<std::uint64_t>(SDL_PeepEvents(nullptr , 0 , SDL_GETEVENT , SDL_KEYDOWN , SDL_KEYUP))};
        SDL_PeepEvents(LEvents.data() , static_cast<std::int32_t>(std::ssize(LEvents)) , SDL_GETEVENT , SDL_KEYDOWN , SDL_KEYUP);
        if(std::ssize(LEvents))
        {
            std::cout << "";
        }
        std::ranges::for_each(LEvents , [&](auto const& AEvent)->void{FKeys[FKeysAdaptors[AEvent.key.keysym.scancode]]->IPostupdate(AEvent.key);});
    }
}