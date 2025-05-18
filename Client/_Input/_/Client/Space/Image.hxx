#pragma once

namespace NOppression::NClient::NSpace
{
    struct SImage
    {
        SDL_Rect FTarget;

        SImage(std::int64_t const& AX , std::int64_t const& AY , std::int64_t const& AWidth , std::int64_t const& AHeight);
        void IDraw(std::int64_t const& AX , std::int64_t const& AY);
    };
}