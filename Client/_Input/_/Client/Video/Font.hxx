#pragma once

namespace NOppression::NClient::NVideo
{
    struct SFont
    {       
        std::vector<std::shared_ptr<SImage>> FDigits;
        std::vector<std::shared_ptr<SImage>> FUppercases;
        std::vector<std::shared_ptr<SImage>> FLowercases;
        std::vector<std::shared_ptr<SImage>> FTerrains;
        std::vector<std::shared_ptr<SImage>> FEntities;

        SFont(std::string const& APath);
        SImage* IDigit(char const& ACode);
        SImage* IUppercase(char const& ACode);
        SImage* ILowercase(char const& ACode);
        SImage* ITerrain(std::int64_t const& AIdentifier);
        SImage* IEntity(std::int64_t const& AIdentifier);
    };
}