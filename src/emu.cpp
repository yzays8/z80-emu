#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <chrono>

#include "emu.hpp"
#include "mmu.hpp"
#include "serial.hpp"
#include "interrupt.hpp"
#include "cpu.hpp"
#include "timer.hpp"

constexpr int kCyclesPerFrame = kCPUFreq / kFrameRate;

Emulator::Emulator()
    : registers_{std::make_shared<Registers>()},
      mmu_{std::make_shared<MMU>()},
      serial_{std::make_shared<Serial>(mmu_)},
      interrupt_{std::make_shared<Interrupt>(registers_, mmu_)},
      cpu_{std::make_shared<CPU>(registers_, mmu_, interrupt_)},
      timer_{std::make_shared<Timer>(mmu_, interrupt_)} {}

void Emulator::LoadCartridge(const std::string& file_path, bool only_header) {
  mmu_->LoadCartridge(file_path, only_header);
}

void Emulator::Run(bool debug) {
  const auto interval = std::chrono::duration<int, std::ratio<1, kFrameRate>>(1);

  for (;;) {
    auto start = std::chrono::high_resolution_clock::now();
    UpdateFrame(debug);
    std::this_thread::sleep_until(start + interval);
  }
}

void Emulator::UpdateFrame(bool debug) {
  int cycles = 0;

  while (cycles < kCyclesPerFrame) {
    int cpu_cycles = cpu_->Tick(debug);
    cycles += cpu_cycles;
    timer_->Tick(cpu_cycles);
    serial_->CheckSerialPort(cpu_cycles);
    cycles += interrupt_->ProcessInterrupt(cpu_->GetHalt());
  }

  // Render
}