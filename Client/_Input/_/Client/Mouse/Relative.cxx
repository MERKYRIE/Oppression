#include"Client.hxx"

namespace NOppression::NClient::NMouse
{
    SRelative::SRelative()
    {
        FModification = false;
        FPixel = std::make_shared<SPixel>();
        FRectangle = std::make_shared<SRectangle>();
        FSquare = std::make_shared<SSquare>();
    }

    SRelative* SRelative::IPreupdate()
    {
        FModification = false;
        FPixel->IPreupdate();
        FRectangle->IPreupdate();
        FSquare->IPreupdate();
        return(this);
    }

    SRelative* SRelative::IPostupdate(SDL_MouseMotionEvent const& AMotion)
    {
        FModification = true;
        FPixel->IPostupdate(AMotion.xrel , AMotion.yrel);
        FRectangle->IPostupdate(AMotion.xrel , AMotion.yrel);
        FSquare->IPostupdate(AMotion.xrel , AMotion.yrel);
        return(this);
    }

    SRelative::~SRelative()
    {
    
    }
}