#include"Client.hxx"

namespace NOppression::NClient::NMouse
{
    SSquare::SSquare()
    {
        FModification = false;
        FX = 0.0;
        FY = 0.0;
    }

    SSquare* SSquare::IPreupdate()
    {
        FModification = false;
        FX = 0.0;
        FY = 0.0;
        return(this);
    }

    SSquare* SSquare::IPostupdate(std::int64_t const& AX , std::int64_t const& AY)
    {
        FModification = true;
        FX = GVideo.IPixelToSquare(AX);
        FY = GVideo.IPixelToSquare(AY);
        return(this);
    }

    SSquare::~SSquare()
    {
    
    }
}