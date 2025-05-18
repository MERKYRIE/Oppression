#pragma once

namespace NOppression::NClient
{
    inline struct SVideo
    {
        SDL_Window * FWindow;
        SDL_Renderer * FRenderer;
        std::int64_t FWidth;
        std::int64_t FHeight;
        std::int64_t FMinimum;
        std::int64_t FMaximum;
        double FRatio;
        double FRatioInversed;
        std::int64_t FWidthProportional;
        std::int64_t FHeightProportional;
        std::unordered_map<std::string , std::shared_ptr<NVideo::SFont>> FFonts;
        std::vector<std::unique_ptr<NVideo::SImage>> FTerrains;
        std::vector<std::unique_ptr<NVideo::SImage>> FEntities;

        SVideo();
        void IUpdate();
        NVideo::SFont * IFont(std::string const& APath);
        NVideo::SImage * ITerrain(std::int64_t const& AIdentifier);
        NVideo::SImage * IEntity(std::int64_t const& AIdentifier);
        double IPixelToRectangleHorizontal(std::int64_t const& APixel);
        double IPixelToRectangleVertical(std::int64_t const& APixel);
        double IPixelToSquare(std::int64_t const& APixel);
        std::int64_t IRectangleToPixelHorizontal(double const& ARectangle);
        std::int64_t IRectangleToPixelVertical(double const& ARectangle);
        double IRectangleToSquareHorizontal(double const& ARectangle);
        double IRectangleToSquareVertical(double const& ARectangle);
        std::int64_t ISquareToPixel(double const& ASquare);
        double ISquareToRectangleHorizontal(double const& ASquare);
        double ISquareToRectangleVertical(double const& ASquare);
        ~SVideo();
    }
    GVideo;
}