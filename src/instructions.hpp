#pragma once

#include <memory>

#include "registers.hpp"
#include "mmu.hpp"

class Instructions {
 public:
  Instructions(std::shared_ptr<Registers> registers, std::shared_ptr<MMU> mmu);

  // returns the number of additional cycles in an instruction with a branch
  int GetBranchCycle();

  void Load(uint16_t& op1);
  void Load(uint8_t& op1);
  void Load(uint8_t& op1, uint8_t op2);
  void Load(uint8_t& op1, uint16_t op2);
  void Load(uint16_t op1, uint8_t op2);

  void Ret(bool flag);
  void Pop(uint16_t& op1);
  void Push(uint16_t& op1);
  void Jp(bool flag);
  void Jr(bool flag);
  void Call(bool flag);
  void Rst(uint16_t addr);

  void Add(uint16_t& op1, uint16_t op2);
  void Add(uint8_t& op1, uint8_t op2);
  void Adc(uint8_t& op1, uint8_t op2);
  void Sub(uint8_t op1);
  void Sbc(uint8_t& op1, uint8_t op2);
  void Inc(uint16_t& op1);
  void Inc(uint8_t& op1);
  void Inc();
  void Dec(uint16_t& op1);
  void Dec(uint8_t& op1);
  void Dec();

  void And(uint8_t op1);
  void Or(uint8_t op1);
  void Xor(uint8_t op1);
  void Cp(uint8_t op1);

  // CB prefixed instructions below

  void Rlc(uint8_t& op1); // rotate left
  void Rlc();
  void Rrc(uint8_t& op1); // rotate right
  void Rrc();
  void Rl(uint8_t& op1);  // rotate left through carry
  void Rl();
  void Rr(uint8_t& op1);  // rotate right through carry
  void Rr();

  void Sla(uint8_t& op1);   // shift left arithmetic
  void Sla();
  void Sra(uint8_t& op1);   // shift right arithmetic
  void Sra();
  void Swap(uint8_t& op1);  // exchange low/hi-nibble
  void Swap();
  void Srl(uint8_t& op1);   // shift right logical
  void Srl();

  void Bit(int op1, uint8_t op2);   // test bit op1 of op2
  void Res(int op1, uint8_t& op2);  // reset bit op1 of op2
  void Res(int op1);
  void Set(int op1, uint8_t& op2);  // set bit op1 of op2
  void Set(int op1);

 private:
  std::shared_ptr<Registers> registers_;
  std::shared_ptr<MMU> mmu_;

  int branch_cycles_;
};
