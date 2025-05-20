#include"Server.hxx"

namespace NOppression::NServer::NNetwork
{
    void IInitialize()
    {
        NDebug::ICode(SDLNet_Init());
        NDebug::ICode(SDLNet_ResolveHost(&GAddress , nullptr , 27015));
        NDebug::IHandle(GSocket = SDLNet_TCP_Open(&GAddress));
        NClient::IInitialize();
        GClientArray.resize(1);
        for(auto & LClient : GClientArray)
        {
            NClient::IConstruct();
            LClient = NClient::GClient;
        }
        GAddressee = -1;
        GAcceptance = nullptr;
        GData = nullptr;
        GSize = 0;
        GIntegral = 0;
    }

    void IUpdate()
    {
        GAddressee = (GAddressee + 1) % std::ssize(GClientArray);
        if(SDLNet_TCP_Recv(NClient::GClientArray[GClientArray[GAddressee]]->FSocket , nullptr , 0) < 0)
        {
            NClient::GClient = GClientArray[GAddressee];
            NClient::IDeconstruct();
            GClientArray.erase(GClientArray.begin() + GAddressee);
        }
    }

    void IAccept()
    {
        GAcceptance = SDLNet_TCP_Accept(GSocket);
    }

    void ISend()
    {
        NDebug::IAssert(SDLNet_TCP_Send(NClient::GClientArray[GClientArray[GAddressee]]->FSocket , GData , static_cast<std::int32_t>(GSize)) != GSize);
    }

    void ISendIntegral()
    {
        GData = &GIntegral;
        GSize = sizeof(GIntegral);
        ISend();
    }

    void IReceive()
    {
        NDebug::IAssert(SDLNet_TCP_Recv(NClient::GClientArray[GClientArray[GAddressee]]->FSocket , GData , static_cast<std::int32_t>(GSize)) != GSize);
    }

    void IReceiveIntegral()
    {
        GData = &GIntegral;
        GSize = sizeof(GIntegral);
        IReceive();
    }

    void IDeinitialize()
    {
        GIntegral = 0;
        GSize = 0;
        GData = nullptr;
        GAcceptance = nullptr;
        GAddressee = -1;
        for(auto const& LClient : GClientArray)
        {
            NClient::GClient = LClient;
            NClient::IDeconstruct();
        }
        GClientArray.clear();
        NClient::IDeinitialize();
        SDLNet_TCP_Close(GSocket);
        GSocket = nullptr;
        SDLNet_Quit();
    }
}