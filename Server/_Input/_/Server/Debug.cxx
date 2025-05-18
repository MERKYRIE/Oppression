#include"Server.hxx"

namespace NOppression::NServer
{
    void SDebug::IAssert(bool const& ACondition , std::string const& AMessage , std::source_location const& ALocation)
    {
        if(ACondition)
        {
            if
            (
                SDL_ShowSimpleMessageBox
                (
                    SDL_MESSAGEBOX_ERROR
                    ,
                    "Debug"
                    ,
                    (std::string{} + "File - " + ALocation.file_name() + "\n" + "Function - " + ALocation.function_name() + "\n" + "Line - " + std::to_string(ALocation.line()) + "\n" + "Column - " + std::to_string(ALocation.column()) + "\n" + AMessage).data()
                    ,
                    nullptr
                )
                < 0
            )
            {
                std::cout << "Debug:" << "\n" << "    File - " << ALocation.file_name() << "\n" << "    Function - " << ALocation.function_name() << "\n" << "    Line - " << ALocation.line() << "\n" << "    Column - " << ALocation.column() << "\n" << AMessage << "\n\n";
            }
            std::exit(0);
        }
    }

    void SDebug::ICode(std::int64_t const& AValue , std::source_location const& ALocation)
    {
        IAssert(AValue < 0 , std::string{} + "Simple DirectMedia Layer - " + SDL_GetError() , ALocation);
    }

    void SDebug::IMask(std::int64_t const& AValue , std::source_location const& ALocation)
    {
        IAssert(!AValue , std::string{} + "Simple DirectMedia Layer - " + SDL_GetError() , ALocation);
    }

    void SDebug::IHandle(void *const& APointer , std::source_location const& ALocation)
    {
        IAssert(!APointer , std::string{} + "Simple DirectMedia Layer - " + SDL_GetError() , ALocation);
    }
}