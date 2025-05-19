#include"Server.hxx"

namespace NOppression::NServer::NNetwork
{
    void IInitialize()
    {
        NDebug::ICode(SDLNet_Init());
        IPaddress LAddress;
        NDebug::ICode(SDLNet_ResolveHost(&LAddress , nullptr , 27015));
        NDebug::IHandle(FSocket = SDLNet_TCP_Open(&LAddress));
        NClient::IInitialize();
        NClient::IConstruct();
        FClientArray.emplace_back(NClient::GConstruction);
        FAddressee = FClientArray[0];
    }

    void IUpdate()
    {
        if(SDLNet_TCP_Recv(NClient::GArray[FAddressee]->FSocket , nullptr , 0) < 0)
        {
            NClient::GDeconstruction = FAddressee;
            NClient::IDeconstruct();
        }
    }

    TCPsocket IAccept()
    {
        return(SDLNet_TCP_Accept(FSocket));
    }

    void ISend(void const*const& AData , std::int64_t const& ASize)
    {
        NDebug::IAssert(SDLNet_TCP_Send(NClient::GArray[FAddressee]->FSocket , AData , static_cast<std::int32_t>(ASize)) != ASize);
    }

    void ISendIntegral(std::int64_t const& AValue)
    {
        ISend(&AValue , sizeof(AValue));
    }

    void IReceive(void *const& AData , std::int64_t const& ASize)
    {
        NDebug::ISimpleDirectMediaLayer(SDLNet_TCP_Recv(NClient::GArray[FAddressee]->FSocket , AData , static_cast<std::int32_t>(ASize)) != ASize);
    }

    void IReceiveIntegral(std::int64_t & AValue)
    {
        IReceive(&AValue , sizeof(AValue));
    }

    void IDeinitialize()
    {
        for(auto const& LClient : FClientArray)
        {
            NClient::GDeconstruction = LClient;
            NClient::IDeconstruct();
        }
        FClientArray.clear();
        NClient::IDeinitialize();
        SDLNet_TCP_Close(FSocket);
        SDLNet_Quit();
    }
}