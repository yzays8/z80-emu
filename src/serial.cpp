#include <iostream>
#include <memory>

#include "serial.hpp"

Serial::Serial(std::shared_ptr<MMU> mmu) : mmu_{mmu}, cycles_{0} {}

void Serial::CheckSerialPort(int cycles) {
  cycles_ += cycles;

  while (cycles_ >= 512) {  // 8192 Hz
    cycles_ -= 512;
    if (mmu_->ReadByte(0xFF02) == 0x81) {
      uint8_t c = mmu_->ReadByte(0xFF01);
      std::cout << static_cast<char>(c) << std::flush;
      mmu_->WriteByte(0xFF02, 0x0);
    }
  }
}
