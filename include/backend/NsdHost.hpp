#pragma once

#include <avahi-common/address.h>
#include <avahi-client/client.h>
#include <variant>

class NsdHost {
public:
    NsdHost(std::variant<AvahiIPv4Address, AvahiIPv6Address> ipAddress);
    ~NsdHost();
};
