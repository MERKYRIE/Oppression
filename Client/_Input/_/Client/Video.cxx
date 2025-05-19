#include"Client.hxx"

namespace NOppression::NClient
{
    SVideo::SVideo()
    {
        GDebug.IHandle(FWindow = SDL_CreateWindow("Oppression" , SDL_WINDOWPOS_CENTERED , SDL_WINDOWPOS_CENTERED , 1600 , 900 , 0));
        GDebug.IHandle(FRenderer = SDL_CreateRenderer(FWindow , -1 , SDL_RENDERER_ACCELERATED));
        SDL_DisplayMode LDisplayMode;
        GDebug.ICode(SDL_GetWindowDisplayMode(FWindow , &LDisplayMode));
        FWidth = LDisplayMode.w;
        FHeight = LDisplayMode.h;
        FMinimum = std::min(FWidth , FHeight);
        FMaximum = std::max(FWidth , FHeight);
        FRatio = static_cast<double>(FWidth) / static_cast<double>(FHeight);
        FRatioInversed = static_cast<double>(FHeight) / static_cast<double>(FWidth);
        FWidthProportional = 0;
        for(FHeightProportional = 3 ; FHeightProportional <= 9 ; FHeightProportional++)
        {
            if(std::abs(FHeightProportional * FRatio - std::round(FHeightProportional * FRatio)) < std::numeric_limits<double>::epsilon())
            {
                FWidthProportional = static_cast<std::int64_t>(std::round(FHeightProportional * FRatio));
                break;
            }
        }
        GDebug.IAssert(!FWidthProportional);
        GDebug.ICode(TTF_Init());
        for(std::filesystem::directory_entry const& LEntry : std::filesystem::recursive_directory_iterator{"Fonts"})
        {
            if(LEntry.path().extension() == ".ttf")
            {
                FFonts.emplace(LEntry.path().generic_string().substr(LEntry.path().generic_string().find('/')) , std::make_shared<NVideo::SFont>(LEntry.path().generic_string()));
            }
        }
        GDebug.IMask(IMG_Init(IMG_INIT_PNG));
        for(std::filesystem::directory_entry const& LEntry : std::filesystem::recursive_directory_iterator{"Images/Terrains"})
        {
            if(LEntry.path().extension() == ".png")
            {
                FTerrains.emplace_back(std::make_unique<NVideo::SImage>(LEntry.path().generic_string()));
            }
        }
        for(std::filesystem::directory_entry const& LEntry : std::filesystem::recursive_directory_iterator{"Images/Entities"})
        {
            if(LEntry.path().extension() == ".png")
            {
                FEntities.emplace_back(std::make_unique<NVideo::SImage>(LEntry.path().generic_string()));
            }
        }
    }

    void SVideo::IUpdate()
    {
        SDL_RenderPresent(FRenderer);
        SDL_RenderClear(FRenderer);
    }

    NVideo::SFont * SVideo::IFont(std::string const& APath)
    {
        return(std::ranges::find_if(FFonts , [&](auto const& AFont)->bool{return(AFont.first == APath);})->second.get());
    }

    NVideo::SImage * SVideo::ITerrain(std::int64_t const& AIdentifier)
    {
        return(FTerrains[AIdentifier].get());
    }

    NVideo::SImage * SVideo::IEntity(std::int64_t const& AIdentifier)
    {
        return(FEntities[AIdentifier].get());
    }

    double SVideo::IPixelToRectangleHorizontal(std::int64_t const& APixel)
    {
        return(static_cast<double>(APixel) / static_cast<double>(FWidth));
    }

    double SVideo::IPixelToRectangleVertical(std::int64_t const& APixel)
    {
        return(static_cast<double>(APixel) / static_cast<double>(FHeight));
    }

    double SVideo::IPixelToSquare(std::int64_t const& APixel)
    {
        return(static_cast<double>(APixel) / static_cast<double>(FMinimum));
    }

    std::int64_t SVideo::IRectangleToPixelHorizontal(double const& ARectangle)
    {
        return(static_cast<std::int64_t>(FWidth * ARectangle));
    }

    std::int64_t SVideo::IRectangleToPixelVertical(double const& ARectangle)
    {
        return(static_cast<std::int64_t>(FHeight * ARectangle));
    }

    double SVideo::IRectangleToSquareHorizontal(double const& ARectangle)
    {
        return(IPixelToSquare(IRectangleToPixelHorizontal(ARectangle)));
    }

    double SVideo::IRectangleToSquareVertical(double const& ARectangle)
    {
        return(IPixelToSquare(IRectangleToPixelVertical(ARectangle)));
    }

    std::int64_t SVideo::ISquareToPixel(double const& ASquare)
    {
        return(static_cast<std::int64_t>(FMinimum * ASquare));
    }

    double SVideo::ISquareToRectangleHorizontal(double const& ASquare)
    {
        return(IPixelToRectangleHorizontal(ISquareToPixel(ASquare)));
    }

    double SVideo::ISquareToRectangleVertical(double const& ASquare)
    {
        return(IPixelToRectangleVertical(ISquareToPixel(ASquare)));
    }

    SVideo::~SVideo()
    {
        FTerrains.clear();
        IMG_Quit();
        FFonts.clear();
        TTF_Quit();
        SDL_DestroyRenderer(FRenderer);
        SDL_DestroyWindow(FWindow);
    }
}