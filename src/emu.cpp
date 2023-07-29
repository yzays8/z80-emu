#include <iostream>
#include <memory>
#include <string>

#include "emu.hpp"
#include "mmu.hpp"
#include "serial.hpp"
#include "interrupt.hpp"
#include "cpu.hpp"
#include "timer.hpp"

Emulator::Emulator(const std::string& file_path)
    : mmu_{std::make_shared<MMU>(file_path)},
      serial_{std::make_shared<Serial>(mmu_)},
      interrupt_{std::make_shared<Interrupt>(mmu_)},
      cpu_{std::make_shared<CPU>(mmu_, interrupt_)},
      timer_{std::make_shared<Timer>(cpu_, mmu_, interrupt_)} {}

void Emulator::Run() {
  mmu_->LoadROMBank0();

  for (;;) {
    cpu_->Tick();
    timer_->Tick();
    serial_->CheckSerialPort();
  }
}
