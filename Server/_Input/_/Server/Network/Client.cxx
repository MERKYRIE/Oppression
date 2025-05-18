#include"Server.hxx"

namespace NOppression::NServer::NNetwork
{
    SClient::SClient()
    {
        GDebug.IHandle(FSet = SDLNet_AllocSocketSet(1));
        std::cout << "Waiting for client to connect..." << "\n";
        FSocket = nullptr;
        while(!FSocket)
        {
   	        FSocket = GNetwork.IAccept();
        }
        std::cout << "Client connected successfully!" << "\n";
        GDebug.ICode(SDLNet_TCP_AddSocket(FSet , FSocket));
    }

    SClient::~SClient()
    {
        GDebug.ICode(SDLNet_TCP_DelSocket(FSet , FSocket));
        SDLNet_TCP_Close(FSocket);
        SDLNet_FreeSocketSet(FSet);
    }
}