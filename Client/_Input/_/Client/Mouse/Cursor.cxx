#include"Client.hxx"

namespace NOppression::NClient::NMouse
{
    SCursor::SCursor()
    {
        FModification = false;
        FAbsolute = std::make_shared<SAbsolute>();
        FRelative = std::make_shared<SRelative>();
    }

    SCursor* SCursor::IPreupdate()
    {
        FModification = false;
        FAbsolute->IPreupdate();
        FRelative->IPreupdate();
        return(this);
    }

    SCursor* SCursor::IPostupdate(SDL_MouseMotionEvent const& AMotion)
    {
        FModification = true;
        FAbsolute->IPostupdate(AMotion);
        FRelative->IPostupdate(AMotion);
        return(this);
    }

    SCursor::~SCursor()
    {
    
    }
}