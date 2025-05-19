#include"Server.hxx"

namespace NOppression::NServer::NNetwork::NClient
{
    void IInitialize()
    {
        GArray[0] = nullptr;
        GConstruction = 0;
        GBindingArray[0] = nullptr;
        GDeconstruction = 0;
    }
    
    void IConstruct()
    {
        GConstruction = std::ranges::max_element(GArray)->first + 1;
        GArray[GConstruction] = new SClient;
        NDebug::IHandle(GArray[GConstruction]->FSet = SDLNet_AllocSocketSet(1));
        std::cout << "Waiting for client to connect..." << "\n";
        GArray[GConstruction]->FSocket = nullptr;
        while(!GArray[GConstruction]->FSocket)
        {
   	        GArray[GConstruction]->FSocket = IAccept();
        }
        std::cout << "Client connected successfully!" << "\n";
        NDebug::ICode(SDLNet_TCP_AddSocket(GArray[GConstruction]->FSet , GArray[GConstruction]->FSocket));
    }

    void IDeconstruct()
    {
        NDebug::ICode(SDLNet_TCP_DelSocket(GArray[GDeconstruction]->FSet , GArray[GDeconstruction]->FSocket));
        SDLNet_TCP_Close(GArray[GDeconstruction]->FSocket);
        SDLNet_FreeSocketSet(GArray[GDeconstruction]->FSet);
    }

    void IDeinitialize()
    {
        GDeconstruction = 0;
        GBindingArray[0] = nullptr;
        GConstruction = 0;
        GArray[0] = nullptr;
    }
}