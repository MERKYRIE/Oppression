#include"Server.hxx"

namespace NOppression::NServer::NTime
{
    void IInitialize()
    {
        GLast = 0.0;
        GAbsolute = 0.0;
        GRelative = 0.0;
    }
    
    void IUpdate()
    {
        GLast = GAbsolute;
        GAbsolute = SDL_GetTicks();
        GRelative = GAbsolute - GLast;
    }

    void IDeinitialize()
    {
        GRelative = 0.0;
        GAbsolute = 0.0;
        GLast = 0.0;
    }
}