#include "backend/NsdHost.hpp"
#include <avahi-common/address.h>
#include <backend/ServerBackend.hpp>
#include <memory>

ServerBackend::ServerBackend(const AvahiAddress &address) {
    ServiceInfo serviceInfo{};
    serviceInfo.serviceName = "TuxControl Server";
    serviceInfo.serviceID = "_tuxcontrol._tcp";

    m_NsdHost = std::make_unique<NsdHost>(address, serviceInfo);
}

ServerBackend::~ServerBackend() {
    /* TODO: clean, probably not necessary with smart pointers */
}
