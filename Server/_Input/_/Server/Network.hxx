#pragma once

namespace NOppression::NServer
{
    inline struct SNetwork
    {
        TCPsocket FSocket;
        std::vector<NNetwork::SClient> FClients;
        std::vector<std::reference_wrapper<NNetwork::SClient>> FAddressees;
        
        SNetwork();
        TCPsocket IAccept();
        void IAddressOne(NNetwork::SClient & AClient);
        void IAddressRest(NNetwork::SClient const& AClient);
        void IAddressAll();
        void ISend(void const*const& AData , std::int64_t const& ASize);
        void ISendIntegral(std::int64_t const& AValue);
        void IReceive(void *const& AData , std::int64_t const& ASize);
        void IReceiveIntegral(std::vector<std::int64_t> & AValue);
        ~SNetwork();
    }
    GNetwork;
}