#include <avahi-common/address.h>
#include <cstdlib>
#include <fmt/core.h>
#include <backend/ServerBackend.hpp>
#include <iostream>

int main() {
    AvahiAddress address;
    avahi_address_parse("192.168.100.16", AVAHI_PROTO_INET, &address);

    ServerBackend serverBackend(address);

    /* Block until CTRL-C */
    while (true) {
        char c;
        std::cin >> c;
    }

    return EXIT_SUCCESS;
}
