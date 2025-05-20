#pragma once

namespace NOppression::NServer::NNetwork
{
    inline TCPsocket FSocket;
    inline std::vector<std::int64_t> FClientArray;
    inline std::int64_t FAddressee;
    inline TCPsocket FAcceptance;
    inline void * FData;
    inline std::int64_t FSize;
    inline std::int64_t * FIntegral;
        
    void IInitialize();
    void IUpdate();
    void IAccept();
    void ISend();
    void ISendIntegral();
    void IReceive();
    void IReceiveIntegral();
    void IDeinitialize();
}