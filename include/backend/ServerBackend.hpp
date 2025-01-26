#pragma once

#include "backend/NsdHost.hpp"
#include <avahi-common/address.h>
#include <memory>
#include <type_traits>
#include <variant>

class ServerBackend {
public:
    ServerBackend(const AvahiAddress &address);
    ~ServerBackend();

    /* Begin hosting the server and make this machine available on the local network */
    void StartServer();
private:
    void InitNsdHost();

    std::unique_ptr<NsdHost> m_NsdHost;
};
