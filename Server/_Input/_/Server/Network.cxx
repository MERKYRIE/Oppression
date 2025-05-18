#include"Server.hxx"

namespace NOppression::NServer
{
    SNetwork::SNetwork()
    {
        GDebug.ICode(SDLNet_Init());
        IPaddress LAddress;
        GDebug.ICode(SDLNet_ResolveHost(&LAddress , nullptr , 27015));
        GDebug.IHandle(FSocket = SDLNet_TCP_Open(&LAddress));
        FClients.emplace_back();
    }

    TCPsocket SNetwork::IAccept()
    {
        return(SDLNet_TCP_Accept(FSocket));
    }

    void SNetwork::IAddressOne(NNetwork::SClient & AClient)
    {
        FAddressees = {AClient};
    }

    void SNetwork::IAddressRest(NNetwork::SClient const& AClient)
    {
        FAddressees.clear();
        for(auto & LClient : FClients)
        {
            if(&AClient != &LClient)
            {
                FAddressees.emplace_back(LClient);
            }
        }
    }

    void SNetwork::IAddressAll()
    {
        FAddressees.clear();
        for(auto & LClient : FClients)
        {
            FAddressees.emplace_back(LClient);
        }
    }

    void SNetwork::ISend(void const*const& AData , std::int64_t const& ASize)
    {
        for(auto const& LAddressee : FAddressees)
        {
            GDebug.IAssert(SDLNet_TCP_Send(LAddressee.get().FSocket , AData , static_cast<std::int32_t>(ASize)) != ASize);
        }
    }

    void SNetwork::ISendIntegral(std::int64_t const& AValue)
    {
        ISend(&AValue , sizeof(AValue));
    }

    void SNetwork::IReceive(void *const& AData , std::int64_t const& ASize)
    {
        for(std::int64_t LAddressee{0} ; LAddressee < std::ssize(FAddressees) ; LAddressee++)
        {
            GDebug.IAssert(SDLNet_TCP_Recv(FAddressees[LAddressee].get().FSocket , static_cast<std::uint8_t *>(AData) + ASize * LAddressee , static_cast<std::int32_t>(ASize)) != ASize);
        }
    }

    void SNetwork::IReceiveIntegral(std::vector<std::int64_t> & AValue)
    {
        AValue.resize(std::ssize(FAddressees));
        IReceive(AValue.data() , sizeof(std::remove_reference_t<decltype(AValue)>::value_type));
    }

    SNetwork::~SNetwork()
    {
        FClients.clear();
        SDLNet_TCP_Close(FSocket);
        SDLNet_Quit();
    }
}