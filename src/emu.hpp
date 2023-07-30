#pragma once

#include <memory>
#include <string>

#include "mmu.hpp"
#include "serial.hpp"
#include "interrupt.hpp"
#include "cpu.hpp"
#include "timer.hpp"

class Emulator {
 public:
  Emulator();
  void LoadCartridge(const std::string& file_path, bool only_header);
  void Run();

 private:
  std::shared_ptr<MMU> mmu_;
  std::shared_ptr<Serial> serial_;
  std::shared_ptr<Interrupt> interrupt_;
  std::shared_ptr<CPU> cpu_;
  std::shared_ptr<Timer> timer_;
};
