#pragma once

namespace NOppression::NServer::NNetwork
{
    inline TCPsocket FSocket;
    inline std::vector<std::int64_t> FClientArray;
    inline std::int64_t FAddressee;
        
    void IInitialize();
    void IUpdate();
    TCPsocket IAccept();
    void ISend(void const*const& AData , std::int64_t const& ASize);
    void ISendIntegral(std::int64_t const& AValue);
    void IReceive(void *const& AData , std::int64_t const& ASize);
    void IReceiveIntegral(std::int64_t & AValue);
    void IDeinitialize();
}