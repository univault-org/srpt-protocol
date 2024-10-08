#ifndef SRPT_NETWORK_LOCAL_DISCOVERY_H
#define SRPT_NETWORK_LOCAL_DISCOVERY_H

#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <atomic>
#include <mutex>

namespace srpt {
namespace network {
namespace local {

class Discovery {
public:
    Discovery();
    ~Discovery();

    bool startDiscovery();
    void stopDiscovery();
    std::vector<std::string> getDiscoveredNodes() const;
    
    void setTimeout(std::chrono::milliseconds timeout);
    bool isDiscoveryActive() const;

private:
    std::vector<std::string> discoveredNodes;
    std::atomic<bool> m_isDiscoveryActive;
    std::chrono::milliseconds timeout;
    std::thread discoveryThread;
    mutable std::mutex discoveredNodesMutex;

    void simulateDiscovery();
};

} // namespace local
} // namespace network
} // namespace srpt

#endif // SRPT_NETWORK_LOCAL_DISCOVERY_H