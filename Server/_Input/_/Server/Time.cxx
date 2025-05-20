#include"Server.hxx"

namespace NOppression::NServer::NTime
{
    void IInitialize()
    {
        FLast = 0.0;
        FAbsolute = 0.0;
        FRelative = 0.0;
    }
    
    void IUpdate()
    {
        FLast = FAbsolute;
        FAbsolute = SDL_GetTicks();
        FRelative = FAbsolute - FLast;
    }

    void IDeinitialize()
    {
        FRelative = 0.0;
        FAbsolute = 0.0;
        FLast = 0.0;
    }
}