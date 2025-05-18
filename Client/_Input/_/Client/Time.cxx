#include"Client.hxx"

namespace NOppression::NClient
{
    void STime::IUpdate()
    {
        FLast = FAbsolute;
        FAbsolute = SDL_GetTicks();
        FRelative = FAbsolute - FLast;
    }
}