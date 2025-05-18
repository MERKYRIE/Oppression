#pragma once

namespace NOppression::NClient::NMouse
{
    struct SButton
    {
        bool FModification;
        std::string FState;
        std::shared_ptr<SCursor> FPressed;
        std::shared_ptr<SCursor> FReleased;
        std::shared_ptr<SCursor> FHeld;

        SButton();
        SButton* IPreupdate();
        SButton* IPostupdate(SDL_Event const& AEvent);
        ~SButton();
    };
}