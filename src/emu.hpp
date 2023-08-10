#pragma once

#include <memory>
#include <string>

#include "registers.hpp"
#include "mmu.hpp"
#include "serial.hpp"
#include "interrupt.hpp"
#include "cpu.hpp"
#include "timer.hpp"

constexpr int kFrameRate = 60;    // 60 Hz

class Emulator {
 public:
  Emulator();
  void LoadCartridge(const std::string& file_path, bool only_header);
  void Run(bool debug);

 private:
  void UpdateFrame(bool debug);

  std::shared_ptr<Registers> registers_;
  std::shared_ptr<MMU> mmu_;
  std::shared_ptr<Serial> serial_;
  std::shared_ptr<Interrupt> interrupt_;
  std::shared_ptr<CPU> cpu_;
  std::shared_ptr<Timer> timer_;
};
