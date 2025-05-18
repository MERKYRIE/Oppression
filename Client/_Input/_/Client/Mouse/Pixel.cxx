#include"Client.hxx"

namespace NOppression::NClient::NMouse
{
    SPixel::SPixel()
    {
        FModification = false;
        FX = 0;
        FY = 0;
    }

    SPixel* SPixel::IPreupdate()
    {
        FModification = false;
        FX = 0;
        FY = 0;
        return(this);
    }

    SPixel* SPixel::IPostupdate(std::int64_t const& AX , std::int64_t const& AY)
    {
        FModification = true;
        FX = AX;
        FY = AY;
        return(this);
    }

    SPixel::~SPixel()
    {
    
    }
}