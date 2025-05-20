#include"Client.hxx"

namespace NOppression::NClient::NSpace
{
    SImage::SImage(std::int64_t const& AX , std::int64_t const& AY , std::int64_t const& AWidth , std::int64_t const& AHeight)
    {
        FTarget = {static_cast<std::int32_t>(AX) , static_cast<std::int32_t>(AY) , static_cast<std::int32_t>(AWidth) , static_cast<std::int32_t>(AHeight)};
    }

    void SImage::IDraw(std::int64_t const& AX , std::int64_t const& AY)
    {
        SDL_RenderCopy(GVideo.FRenderer , GVideo.ITerrain(GSpace.FTerrainArray[AY * GSpace.FWidth + AX])->FHandle , nullptr , &FTarget);
        SDL_RenderCopy(GVideo.FRenderer , GVideo.IEntity(GSpace.FEntityArray[AY * GSpace.FWidth + AX])->FHandle , nullptr , &FTarget);
    }
}