#include <memory>

#include "serial.hpp"

Serial::Serial(std::shared_ptr<MMU> mmu) : mmu_{mmu} {}

void Serial::CheckSerialPort() {
  if (mmu_->ReadByte(0xFF02) == 0x81) {
    char c = mmu_->ReadByte(0xFF01);
    printf("%c", c);
    mmu_->WriteByte(0xFF02, 0x0);
  }
}
