#include <cstdint>
#include <memory>

#include "interrupt.hpp"
#include "registers.hpp"
#include "mmu.hpp"

const std::array<uint16_t, 5> kInterruptHandler = {0x0040, 0x0048, 0x0050, 0x0058, 0x0060};

Interrupt::Interrupt(std::shared_ptr<Registers> registers, std::shared_ptr<MMU> mmu)
    : ime_{0},
      registers_{registers},
      mmu_{mmu} {
  mmu_->WriteByte(0xFF0F, 0xE1);
}

void Interrupt::SetIME(bool ime) {
  ime_ = ime;
}

void Interrupt::SetIE(InterruptType type) {
  mmu_->WriteByte(0xFFFF, mmu_->ReadByte(0xFFFF) | (0x1 << type));
}

void Interrupt::SetIF(InterruptType type) {
  mmu_->WriteByte(0xFF0F, mmu_->ReadByte(0xFF0F) | (0x1 << type));
}

void Interrupt::ResetIF(int type) {
  mmu_->WriteByte(0xFF0F, mmu_->ReadByte(0xFF0F) ^ (0x1 << type));
}

bool Interrupt::GetIME() {
  return ime_;
}

uint8_t Interrupt::GetIE() {
  return mmu_->ReadByte(0xFFFF);
}

uint8_t Interrupt::GetIF() {
  return mmu_->ReadByte(0xFF0F);
}

int Interrupt::CheckInterrupt() {
  uint8_t if_register = GetIF();
  uint8_t ie_register = GetIE();
  int i;

  for (i = 0; i < 5; ++i) {
    if ((if_register & 0x1) && (ie_register & 0x1)) {
      break;
    }
    if_register >>= 1;
    ie_register >>= 1;
  }
  return i;
}

void Interrupt::ProcessInterrupt(bool& halt) {
  int interrupt_type = CheckInterrupt();

  if (interrupt_type != NO_INTERRUPT) {
    // HALT waits for IF and IE to be non-zero
    halt = false;
  }

  if (GetIME()) {
    if (interrupt_type != NO_INTERRUPT) {
      SetIME(false);
      ResetIF(interrupt_type);
      registers_->sp -= 2;  // extend stack
      mmu_->WriteShort(registers_->sp, registers_->pc); // push pc to stack
      registers_->pc = kInterruptHandler[interrupt_type];
    }
  }
}