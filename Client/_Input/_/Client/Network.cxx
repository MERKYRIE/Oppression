#include"Client.hxx"

namespace NOppression::NClient
{
    SNetwork::SNetwork()
    {
        GDebug.ICode(SDLNet_Init());
        /*
        std::cout << "Address to connect (wildcards like 'localhost' are also available): ";
        std::string LAddress;
        std::cin >> LAddress;
        */
        std::string LServer{"localhost"};
        IPaddress LAddress;
        GDebug.ICode(SDLNet_ResolveHost(&LAddress , LServer.data() , 27015));
        GDebug.IHandle(FSet = SDLNet_AllocSocketSet(1));
        std::cout << "Waiting for server to host..." << "\n";
        FSocket = nullptr;
        while(!FSocket)
        {
            FSocket = SDLNet_TCP_Open(&LAddress);
        }
        std::cout << "Server hosted successfully!" << "\n";
        GDebug.ICode(SDLNet_TCP_AddSocket(FSet , FSocket));
    }

    bool SNetwork::IReady()
    {
        std::int32_t LReady{SDLNet_CheckSockets(FSet , 0)};
        GDebug.ICode(LReady);
        return(LReady);
    }

    void SNetwork::ISend(void const*const& AData , std::int64_t const& ASize)
    {
        GDebug.IAssert(SDLNet_TCP_Send(FSocket , AData , static_cast<std::int32_t>(ASize)) != ASize);
    }

    void SNetwork::ISendIntegral(std::int64_t const& AValue)
    {
        ISend(&AValue , sizeof(AValue));
    }

    void SNetwork::IReceive(void *const& AData , std::int64_t const& ASize)
    {
        GDebug.IAssert(SDLNet_TCP_Recv(FSocket , AData , static_cast<std::int32_t>(ASize)) != ASize);
    }

    void SNetwork::IReceiveIntegral(std::int64_t & AValue)
    {
        IReceive(&AValue , sizeof(AValue));
    }

    SNetwork::~SNetwork()
    {
        GDebug.ICode(SDLNet_TCP_DelSocket(FSet , FSocket));
        SDLNet_TCP_Close(FSocket);
        SDLNet_FreeSocketSet(FSet);
        SDLNet_Quit();
    }
}