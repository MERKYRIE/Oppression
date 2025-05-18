#pragma once

namespace NOppression::NClient
{
    inline struct SNetwork
    {
        SDLNet_SocketSet FSet;
        TCPsocket FSocket;
        
        SNetwork();
        bool IReady();
        void ISend(void const*const& AData , std::int64_t const& ASize);
        void ISendIntegral(std::int64_t const& AValue);
        void IReceive(void *const& AData , std::int64_t const& ASize);
        void IReceiveIntegral(std::int64_t & AValue);
        ~SNetwork();
    }
    GNetwork;
}