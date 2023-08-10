#pragma once

#include <cstdint>
#include <array>
#include <memory>

#include "mmu.hpp"
#include "registers.hpp"
#include "instructions.hpp"
#include "interrupt.hpp"

constexpr int kCPUFreq = 4194304; // 4.194304 MHz

extern const std::array<int, 0x100> tcycles_table_;
extern const std::array<int, 0x100> tcycles_table_cb_prefixed_;

class CPU {
 public:
  CPU(std::shared_ptr<Registers> registers, std::shared_ptr<MMU> mmu, std::shared_ptr<Interrupt> interrupt);
  int Tick(bool debug);
  bool& GetHalt() { return halt_; }

 private:
  void InterpretInstruction(uint8_t opcode);
  void InterpretInstructionCB(uint8_t opcode);
  void DebugInstruction(uint8_t opcode);

  std::shared_ptr<Registers> registers_;
  std::shared_ptr<MMU> mmu_;
  std::shared_ptr<Interrupt> interrupt_;
  std::shared_ptr<Instructions> instructions_;

  bool halt_;
};
