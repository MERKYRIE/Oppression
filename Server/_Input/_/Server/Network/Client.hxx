#pragma once

namespace NOppression::NServer::NNetwork
{
    struct SClient
    {
        SDLNet_SocketSet FSet;
        TCPsocket FSocket;

        SClient();
        ~SClient();
    };
}