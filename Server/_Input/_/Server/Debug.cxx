#include"Server.hxx"
#include"Debug.hxx"

namespace NOppression::NServer::NDebug
{
    SDebug GDebug;
    
    std::unordered_map<std::string , std::int64_t> GIntegralArray;
    std::unordered_map<std::string , double> GRealArray;
    std::unordered_map<std::string , std::function<void()>> GFunctionArray;
    std::string GCommand;
    std::string GLexem;
    std::string GVariable;
    std::string GValue;
    std::string GType;

    void SDebug::ITest()
    {
        GIntegralArray["Test"] = 0;
        GRealArray["Check"] = 0.0;
        GFunctionArray["Experiment"] = []{std::cout << "Experiment" << "\n";};
        GCommand = "Test=5\nCheck=3.14\nExperiment()\n";
        GType = "Integral";
        for(char const& LCharacter : GCommand)
        {
            switch(LCharacter)
            {
                case('('):
                    GType = "Function";
                break;
                case(')'):
                    GType = "Function";
                break;
                case('='):
                    GVariable = GLexem;
                    GLexem.clear();
                break;
                case('.'):
                    GType = "Real";
                    GLexem += LCharacter;
                break;
                case('\n'):
                    GValue = GLexem;
                    GLexem.clear();
                    if(GType == "Integral")
                    {
                        GIntegralArray[GVariable] = std::stoll(GValue);
                    }
                    else if(GType == "Real")
                    {
                        GRealArray[GVariable] = std::stod(GValue);
                    }
                    else
                    {
                        GFunctionArray[GValue]();
                    }
                break;
                default:
                    GLexem += LCharacter;
                break;
            }
        }
    }
    
    void IAssert(bool const& ACondition , std::string const& AMessage , std::source_location const& ALocation)
    {
        GDebug.ITest();
        
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