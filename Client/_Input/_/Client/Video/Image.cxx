#include"Client.hxx"

namespace NOppression::NClient::NVideo
{
    SImage::SImage(std::string const& APath)
    {
        FPath = APath.substr(APath.find('/') + 1).substr(APath.substr(APath.find('/') + 1).find('/'));
        FHandle = IMG_LoadTexture(GVideo.FRenderer , APath.c_str());
        GDebug.IHandle(FHandle);
    }

    SImage::SImage(TTF_Font * const& AFont , std::string const& AString)
    {
        SDL_Surface * LSurface{TTF_RenderUTF8_LCD_Wrapped(AFont , (std::string{} + "\n" + " " + AString + " " + "\n").c_str() , SDL_Color{.r{100} , .g{100} , .b{100} , .a{SDL_ALPHA_OPAQUE}} , SDL_Color{.r{0} , .g{0} , .b{0} , .a{SDL_ALPHA_OPAQUE}} , 0)};
        GDebug.IHandle(LSurface);
        FHandle = SDL_CreateTextureFromSurface(GVideo.FRenderer , LSurface);
        GDebug.IHandle(FHandle);
        SDL_FreeSurface(LSurface);
    }

    double SImage::IWidth()
    {
        std::int32_t LWidth;
        SDL_QueryTexture(FHandle , nullptr , nullptr , &LWidth , nullptr);
        return LWidth;
    }

    double SImage::IHeight()
    {
        std::int32_t LHeight;
        SDL_QueryTexture(FHandle , nullptr , nullptr , nullptr , &LHeight);
        return LHeight;
    }

    double SImage::IMinimum()
    {
        std::int32_t LWidth;
        std::int32_t LHeight;
        SDL_QueryTexture(FHandle , nullptr , nullptr , &LWidth , &LHeight);
        return(std::min(LWidth , LHeight));
    }

    double SImage::IMaximum()
    {
        std::int32_t LWidth;
        std::int32_t LHeight;
        SDL_QueryTexture(FHandle , nullptr , nullptr , &LWidth , &LHeight);
        return(std::max(LWidth , LHeight));
    }

    SImage::~SImage()
    {
        SDL_DestroyTexture(FHandle);
    }
}