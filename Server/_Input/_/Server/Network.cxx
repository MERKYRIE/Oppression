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
        FClientArray.resize(1);
        for(auto & LClient : FClientArray)
        {
            NClient::IConstruct();
            LClient = NClient::GClient;
        }
        FAddressee = FClientArray[0];
    }

    void IUpdate()
    {
        if(SDLNet_TCP_Recv(NClient::GClientArray[FAddressee]->FSocket , nullptr , 0) < 0)
        {
            NClient::GClient = FAddressee;
            NClient::IDeconstruct();
            FClientArray.erase(FClientArray.begin() + FAddressee - 1);
        }
    }

    void IAccept()
    {
        FAcceptance = SDLNet_TCP_Accept(FSocket);
    }

    void ISend()
    {
        NDebug::IAssert(SDLNet_TCP_Send(NClient::GClientArray[FAddressee]->FSocket , FData , static_cast<std::int32_t>(FSize)) != FSize);
    }

    void ISendIntegral()
    {
        FData = FIntegral;
        FSize = sizeof(*FIntegral);
        ISend();
    }

    void IReceive()
    {
        NDebug::IAssert(SDLNet_TCP_Recv(NClient::GClientArray[FAddressee]->FSocket , FData , static_cast<std::int32_t>(FSize)) != FSize);
    }

    void IReceiveIntegral()
    {
        FData = FIntegral;
        FSize = sizeof(*FIntegral);
        IReceive();
    }

    void IDeinitialize()
    {
        for(auto const& LClient : FClientArray)
        {
            NClient::GClient = LClient;
            NClient::IDeconstruct();
        }
        FClientArray.clear();
        NClient::IDeinitialize();
        SDLNet_TCP_Close(FSocket);
        SDLNet_Quit();
    }
}