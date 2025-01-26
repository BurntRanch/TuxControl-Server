#include "backend/NsdHost.hpp"
#include <avahi-common/address.h>
#include <backend/ServerBackend.hpp>
#include <memory>
#include <variant>

ServerBackend::ServerBackend(std::variant<AvahiIPv4Address, AvahiIPv6Address> ipAddress) {
    m_NsdHost = std::make_unique<NsdHost>(ipAddress);
}

ServerBackend::~ServerBackend() {
    /* TODO: clean, probably not necessary with smart pointers */
}
