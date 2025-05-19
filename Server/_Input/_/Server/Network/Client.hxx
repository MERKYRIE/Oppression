#pragma once

namespace NOppression::NServer::NNetwork::NClient
{
    struct SClient
    {
        SDLNet_SocketSet FSet;
        TCPsocket FSocket;
    };

    inline std::unordered_map<std::int64_t , SClient *> GArray;
    inline std::int64_t GConstruction;
    inline std::unordered_map<std::int64_t , SClient *> GBindingArray;
    inline std::int64_t GDeconstruction;

    void IInitialize();
    void IConstruct();
    void IDeconstruct();
    void IDeinitialize();
}