#include "transfer_interface/transfer.h"
#include <complex>
#include <cstdint>
#include <cstring>
#include <regex.h>
#include <stdexcept>
#include <sys/types.h>
#include <system/system.h>

ISDRStreamTransfer::Handler handlerFFT = [](void *buff, size_t len) {
  std::complex<double> *signal = new std::complex<double>[len / 2];
  double *power = new double[len];
  std::memcpy(signal, buff, len * sizeof(double));

  power = do_fft(signal, len);
  find_signals(power, len, 100, 1);
};

std::vector<detected_signal *>
SignalSystem::scanPartOfSpectrum(uint64_t startFreqInMHz,
                                 uint64_t stopFreqInMHz, uint64_t sampleRate) {
  if (sdrRf == nullptr || sdrTransfer == nullptr) {
    throw std::runtime_error("sdrRf=nullptr || sdrTransfer=nullptr");
  }

  if (startFreqInMHz == stopFreqInMHz && stopFreqInMHz < startFreqInMHz) {
    throw std::runtime_error("wrong freqs");
  }
  TransferParams params(1, TransferParams::Type::single, sampleRate * 1000000,
                        sampleRate * 1000000);

  sdrRf->setSampleRate(sampleRate * 1000000);
  int count = (stopFreqInMHz - startFreqInMHz) / sampleRate;
  uint64_t currentCentralFreq = startFreqInMHz + sampleRate / 2;
  sdrTransfer->setParam(params);

  for (int i = 0; i != count; i++) {
    sdrRf->setFrequency(currentCentralFreq);
    sdrTransfer->start();
    currentCentralFreq += sampleRate;
  }
}
