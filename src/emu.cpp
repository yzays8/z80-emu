#include <iostream>
#include <memory>
#include <string>

#include "emu.hpp"
#include "mmu.hpp"
#include "serial.hpp"
#include "interrupt.hpp"
#include "cpu.hpp"
#include "timer.hpp"

Emulator::Emulator()
    : mmu_{std::make_shared<MMU>()},
      serial_{std::make_shared<Serial>(mmu_)},
      interrupt_{std::make_shared<Interrupt>(mmu_)},
      cpu_{std::make_shared<CPU>(mmu_, interrupt_)},
      timer_{std::make_shared<Timer>(cpu_, mmu_, interrupt_)} {}

void Emulator::LoadCartridge(const std::string& file_path, bool only_header) {
  mmu_->LoadCartridge(file_path, only_header);
}

void Emulator::Run(bool debug) {
  for (;;) {
    cpu_->Tick(debug);
    timer_->Tick();
    serial_->CheckSerialPort();
  }
}
