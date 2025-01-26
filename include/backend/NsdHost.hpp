#pragma once

#include <avahi-common/address.h>
#include <avahi-client/client.h>
#include <avahi-client/lookup.h>
#include <avahi-client/publish.h>
#include <avahi-common/thread-watch.h>
#include <string>
#include <variant>

struct ServiceInfo {
    std::string serviceName;
    std::string serviceID;
};

class NsdHost {
public:
    NsdHost(const AvahiAddress &address, const ServiceInfo &serviceID);
    ~NsdHost();

    void SetEntryGroup(AvahiEntryGroup *entryGroup);

    ServiceInfo GetServiceInfo();
    AvahiEntryGroup *GetEntryGroup();
    AvahiThreadedPoll *GetPoll();
private:
    ServiceInfo m_ServiceInfo;

    AvahiThreadedPoll *m_ThreadedPoll = nullptr;
    AvahiEntryGroup *m_EntryGroup = nullptr;
    AvahiClient *m_Client = nullptr;
};
