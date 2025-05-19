#pragma once

namespace NOppression::NServer::NDebug
{
    void IAssert(bool const& ACondition = true , std::string const& AMessage = "" , std::source_location const& ALocation = std::source_location::current());
    void ISimpleDirectMediaLayer(bool const& ACondition = true , std::source_location const& ALocation = std::source_location::current());
    void ICode(std::int64_t const& AValue , std::source_location const& ALocation = std::source_location::current());
    void IMask(std::int64_t const& AValue , std::source_location const& ALocation = std::source_location::current());
    void IHandle(void const*const& AValue , std::source_location const& ALocation = std::source_location::current());
}