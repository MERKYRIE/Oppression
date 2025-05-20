#include"Server.hxx"

namespace NOppression::NServer::NNetwork::NClient
{
    void IInitialize()
    {
        GClientArray[0] = nullptr;
        GClient = 0;
    }
    
    void IConstruct()
    {
        GClient = std::ranges::max_element(GClientArray)->first + 1;
        GClientArray[GClient] = new SClient;
        NDebug::IHandle(GClientArray[GClient]->FSet = SDLNet_AllocSocketSet(1));
        std::cout << "Waiting for client to connect..." << "\n";
        GClientArray[GClient]->FSocket = nullptr;
        while(!GClientArray[GClient]->FSocket)
        {
            IAccept();
   	        GClientArray[GClient]->FSocket = FAcceptance;
        }
        std::cout << "Client connected successfully!" << "\n";
        NDebug::ICode(SDLNet_TCP_AddSocket(GClientArray[GClient]->FSet , GClientArray[GClient]->FSocket));
    }

    void IDeconstruct()
    {
        NDebug::ICode(SDLNet_TCP_DelSocket(GClientArray[GClient]->FSet , GClientArray[GClient]->FSocket));
        SDLNet_TCP_Close(GClientArray[GClient]->FSocket);
        SDLNet_FreeSocketSet(GClientArray[GClient]->FSet);
        delete GClientArray[GClient];
        GClientArray.erase(GClient);
    }

    void IDeinitialize()
    {
        GClient = 0;
        GClientArray.clear();
    }
}