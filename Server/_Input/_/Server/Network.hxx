#pragma once

namespace NOppression::NServer::NNetwork
{
    inline IPaddress GAddress;
    inline TCPsocket GSocket;
    inline std::vector<std::int64_t> GClientArray;
    inline std::int64_t GAddressee;
    inline TCPsocket GAcceptance;
    inline void * GData;
    inline std::int64_t GSize;
    inline std::int64_t GIntegral;
        
    void IInitialize();
    void IUpdate();
    void IAccept();
    void ISend();
    void ISendIntegral();
    void IReceive();
    void IReceiveIntegral();
    void IDeinitialize();
}