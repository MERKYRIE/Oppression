#include"Server.hxx"
#include"Debug.hxx"

namespace NOppression::NServer::NDebug
{
    void IAssert(bool const& ACondition , std::string const& AMessage , std::source_location const& ALocation)
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

    void ISimpleDirectMediaLayer(bool const& ACondition , std::source_location const& ALocation)
    {
        IAssert(ACondition , std::string{} + "Simple DirectMedia Layer - " + SDL_GetError() , ALocation);
    }

    void ICode(std::int64_t const& AValue , std::source_location const& ALocation)
    {
        ISimpleDirectMediaLayer(AValue < 0 , ALocation);
    }

    void IMask(std::int64_t const& AValue , std::source_location const& ALocation)
    {
        ISimpleDirectMediaLayer(!AValue , ALocation);
    }

    void IHandle(void const*const& AValue , std::source_location const& ALocation)
    {
        ISimpleDirectMediaLayer(!AValue , ALocation);
    }
}