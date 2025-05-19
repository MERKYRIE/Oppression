#include"Server.hxx"

namespace NOppression::NServer::NTime
{
    void IUpdate()
    {
        FLast = FAbsolute;
        FAbsolute = SDL_GetTicks();
        FRelative = FAbsolute - FLast;
    }
}