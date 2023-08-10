#pragma once

#include <cstdint>
#include <array>
#include <memory>

#include "registers.hpp"
#include "mmu.hpp"

enum InterruptType {
  INTERRUPT_VBLANK,
  INTERRUPT_LCD,
  INTERRUPT_TIMER,
  INTERRUPT_SERIAL_LINK,
  INTERRUPT_JOYPAD,
  NO_INTERRUPT
};

extern const std::array<uint16_t, 5> kInterruptHandler;

class Interrupt {
 public:
  Interrupt(std::shared_ptr<Registers> registers, std::shared_ptr<MMU> mmu);

  void SetIME(bool ime);
  void SetIE(InterruptType type);
  void SetIF(InterruptType type); // requests interrupt
  void ResetIF(int type);
  bool GetIME();
  uint8_t GetIE();
  uint8_t GetIF();

  int ProcessInterrupt(bool& halt);
  int CheckInterrupt();

 private:
  bool ime_;
  std::shared_ptr<Registers> registers_;
  std::shared_ptr<MMU> mmu_;
};
