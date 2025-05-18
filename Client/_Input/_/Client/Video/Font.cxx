#include"Client.hxx"

namespace NOppression::NClient::NVideo
{
    SFont::SFont(std::string const& APath)
    {
        TTF_Font* LFont{TTF_OpenFont(APath.c_str() , 64)};
        GDebug.IHandle(LFont);
        for(char LDigit{'0'} ; LDigit <= '9' ; LDigit++)
        {
            FDigits.emplace_back(std::make_shared<NVideo::SImage>(LFont , std::string{LDigit}));
        }
        FDigits.shrink_to_fit();
        for(char LUppercase{'A'} ; LUppercase <= 'Z' ; LUppercase++)
        {
            FUppercases.emplace_back(std::make_shared<NVideo::SImage>(LFont , std::string{LUppercase}));
        }
        FUppercases.shrink_to_fit();
        for(char LLowercase{'a'} ; LLowercase <= 'z' ; LLowercase++)
        {
            FLowercases.emplace_back(std::make_shared<NVideo::SImage>(LFont , std::string{LLowercase}));
        }
        FLowercases.shrink_to_fit();
        {
            std::fstream LStream{"Strings/Terrains.txt" , std::ios::in};
            std::int64_t LIdentifier{0};
            while(LStream)
            {
                std::string LString;
                LStream >> LString;
                if(LStream)
                {
                    FTerrains.emplace_back(std::make_shared<SImage>(LFont , LString));
                    LIdentifier++;
                }
            }
        }
        {
            std::fstream LStream{"Strings/Entities.txt" , std::ios::in};
            std::int64_t LIdentifier{0};
            while(LStream)
            {
                std::string LString;
                LStream >> LString;
                if(LStream)
                {
                    FEntities.emplace_back(std::make_shared<SImage>(LFont , LString));
                    LIdentifier++;
                }
            }
        }
        TTF_CloseFont(LFont);
    }

    SImage* SFont::IDigit(char const& ACode)
    {
        return(FDigits[static_cast<std::int64_t>(ACode) - static_cast<std::int64_t>('0')].get());
    }

    SImage* SFont::IUppercase(char const& ACode)
    {
        return(FUppercases[static_cast<std::int64_t>(ACode) - static_cast<std::int64_t>('A')].get());
    }

    SImage* SFont::ILowercase(char const& ACode)
    {
        return(FLowercases[static_cast<std::int64_t>(ACode) - static_cast<std::int64_t>('a')].get());
    }

    SImage* SFont::ITerrain(std::int64_t const& AIdentifier)
    {
        return(FTerrains[AIdentifier].get());
    }

    SImage* SFont::IEntity(std::int64_t const& AIdentifier)
    {
        return(FEntities[AIdentifier].get());
    }
}