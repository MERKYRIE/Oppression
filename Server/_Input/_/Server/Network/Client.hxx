#pragma once

namespace NOppression::NServer::NNetwork::NClient
{
    struct SClient
    {
        SDLNet_SocketSet FSet;
        TCPsocket FSocket;
    };

    inline std::unordered_map<std::int64_t , SClient *> GClientArray;
    inline std::int64_t GClient;

    void IInitialize();
    void IConstruct();
    void IDeconstruct();
    void IDeinitialize();
}