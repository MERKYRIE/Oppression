#include"Server.hxx"

namespace NOppression::NServer
{
    void STime::IUpdate()
    {
        FLast = FAbsolute;
        FAbsolute = SDL_GetTicks();
        FRelative = FAbsolute - FLast;
    }
}