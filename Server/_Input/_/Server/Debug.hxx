#pragma once

namespace NOppression::NServer::NDebug
{
    #define PTest()
    
    struct SDebug
    {
        std::unordered_map<std::string , std::int64_t *> GTest;
        std::int64_t FTest; std::function<void()> FFF = [&]{GTest["Test"] = &FTest;;

        void ITest();
    }
    extern GDebug;
    
    void IAssert(bool const& ACondition = true , std::string const& AMessage = "" , std::source_location const& ALocation = std::source_location::current());
    void ISimpleDirectMediaLayer(bool const& ACondition = true , std::source_location const& ALocation = std::source_location::current());
    void ICode(std::int64_t const& AValue , std::source_location const& ALocation = std::source_location::current());
    void IMask(std::int64_t const& AValue , std::source_location const& ALocation = std::source_location::current());
    void IHandle(void const*const& AValue , std::source_location const& ALocation = std::source_location::current());
}