#pragma once
#include "../../include/srpt_satellite.h"
#include <deque>

namespace SRPT {
namespace Satellite {

class StarlinkProvider : public ISatelliteProvider {
public:
    bool Initialize(const std::map<std::string, std::string>& options) override;
    bool Connect(const std::string& satellite_id) override;
    bool Disconnect() override;
    bool SendData(const ByteVector& data) override;
    bool ReceiveData(ByteVector& data) override;
    bool ExecuteCommand(const std::string& command, std::string& response) override;
    double GetSignalStrength() const override;
    double GetLatency() const override;
    uint64_t GetBandwidth() const override;
    std::unique_ptr<SatelliteStream> CreateStream() override;
    void setVerboseLogging(bool verbose) override {m_verboseLogging = verbose;};

private:
    std::deque<ByteVector> m_dataQueue;
    bool m_verboseLogging = false;
    class StarlinkStream : public SatelliteStream {
    public:
        explicit StarlinkStream(StarlinkProvider& provider);
        bool Write(const ByteVector& data) override;
        bool Read(ByteVector& data) override;
        void Close() override;

    private:
        StarlinkProvider& m_provider;
    };
};

} // namespace Satellite
} // namespace SRPT