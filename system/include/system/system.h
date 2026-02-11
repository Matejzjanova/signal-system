#include "detector/detector.h"
#include "nlohmann/json.hpp"
#include "rtlsdr_control.h"
#include "sdr_rf_interface/sdr_rf.h"
#include "transfer_interface/transfer.h"
#include <cstdint>
#include <nlohmann/json_fwd.hpp>
#include <vector>

class SignalSystem {
public:
  SignalSystem(IDeviceRF *deviceRf, ISDRStreamTransfer *deviceTransfer)
      : sdrRf(deviceRf), sdrTransfer(deviceTransfer) {}

  std::vector<detected_signal *> scanPartOfSpectrum(uint64_t from, uint64_t to,
                                                    uint64_t sampleRate);
  nlohmann::json parseSignals(std::vector<detected_signal *> &&signals);

  void sendParsedSignals(nlohmann::json parseSignals);
  nlohmann::json receiveReceiveTask();
  void startReceive(double centralFreq, detected_signal signal);

private:
  IDeviceRF *sdrRf;
  ISDRStreamTransfer *sdrTransfer;

  std::vector<detected_signal *> signals;
};
