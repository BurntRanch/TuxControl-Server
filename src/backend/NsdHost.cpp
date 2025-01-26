#include <avahi-client/lookup.h>
#include <avahi-client/client.h>
#include <avahi-client/publish.h>
#include <avahi-common/alternative.h>
#include <avahi-common/defs.h>
#include <avahi-common/thread-watch.h>
#include <avahi-common/malloc.h>
#include <avahi-common/error.h>
#include <avahi-common/timeval.h>
#include <avahi-common/watch.h>
#include <fmt/core.h>
#include <backend/NsdHost.hpp>
#include <cassert>
#include <fmt/format.h>
#include <stdexcept>

void create_service(AvahiClient *client, NsdHost *host) {
    ServiceInfo serviceInfo = host->GetServiceInfo();

    AvahiEntryGroup *entryGroup = avahi_entry_group_new(client, nullptr, nullptr);
    assert(entryGroup);

    host->SetEntryGroup(entryGroup);

    if (avahi_entry_group_is_empty(entryGroup)) {
        int ret = avahi_entry_group_add_service(
            entryGroup, AVAHI_IF_UNSPEC, AVAHI_PROTO_UNSPEC, AVAHI_PUBLISH_USE_MULTICAST,
            serviceInfo.serviceName.c_str(), serviceInfo.serviceID.c_str(), NULL, NULL, 8080, NULL);

        if (ret < 0) {
            throw std::runtime_error(fmt::format("Failed to add service: {}", avahi_strerror(ret)));
        }

        ret = avahi_entry_group_commit(entryGroup);
        if (ret < 0) {
            throw std::runtime_error(fmt::format("Failed to commit entry group: {}", avahi_strerror(ret)));
            return;
        }

        fmt::println("Service published successfully!");
    }
}

void ClientCallback(AvahiClient *client, AvahiClientState state, void *userdata) {
    NsdHost *host = reinterpret_cast<NsdHost *>(userdata);

    switch (state) {
        case AVAHI_CLIENT_S_RUNNING:
            fmt::println("Avahi client is running. Publishing service...");
            create_service(client, host);
            break;

        case AVAHI_CLIENT_FAILURE:
            fmt::println("Avahi client failure: %s\n", avahi_strerror(avahi_client_errno(client)));
            avahi_threaded_poll_quit(host->GetPoll());
            break;

        case AVAHI_CLIENT_S_COLLISION:
        case AVAHI_CLIENT_S_REGISTERING:
            printf("Avahi is resolving a name conflict or registering.\n");
            avahi_entry_group_reset(host->GetEntryGroup());
            break;

        default:
            break;
    }
}

NsdHost::NsdHost(const AvahiAddress &ipAddress, const ServiceInfo &serviceInfo) {
    m_ServiceInfo = serviceInfo;

    m_ThreadedPoll = avahi_threaded_poll_new();
    assert(m_ThreadedPoll);

    int error = 0;
    m_Client = avahi_client_new(avahi_threaded_poll_get(m_ThreadedPoll), (AvahiClientFlags)0, &ClientCallback, this, &error);

    if (!m_Client) {
        throw std::runtime_error(fmt::format("Failed to create client: {}",
                avahi_strerror(avahi_client_errno(m_Client))));
    }
}

NsdHost::~NsdHost() {

}

void NsdHost::SetEntryGroup(AvahiEntryGroup *entryGroup) {
    m_EntryGroup = entryGroup;
}

ServiceInfo NsdHost::GetServiceInfo() {
    return m_ServiceInfo;
}

AvahiEntryGroup *NsdHost::GetEntryGroup() {
    return m_EntryGroup;
}

AvahiThreadedPoll *NsdHost::GetPoll() {
    return m_ThreadedPoll;
}
