#pragma once

namespace NOppression::NServer
{
    inline struct SDebug
    {
        void IAssert(bool const& ACondition = true , std::string const& AMessage = "" , std::source_location const& ALocation = std::source_location::current());
        void ICode(std::int64_t const& AValue , std::source_location const& ALocation = std::source_location::current());
        void IMask(std::int64_t const& AValue , std::source_location const& ALocation = std::source_location::current());
        void IHandle(void *const& APointer , std::source_location const& ALocation = std::source_location::current());
    }
    GDebug;
}