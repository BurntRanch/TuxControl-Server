#pragma once

#include "backend/NsdHost.hpp"
#include <avahi-common/address.h>
#include <memory>
#include <variant>

class ServerBackend {
public:
    ServerBackend(std::variant<AvahiIPv4Address, AvahiIPv6Address> ipAddress);
    ~ServerBackend();

    /* Begin hosting the server and make this machine available on the local network */
    void StartServer();
private:
    void InitNsdHost();

    std::unique_ptr<NsdHost> m_NsdHost;
};
