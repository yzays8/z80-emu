#include <iostream>
#include <memory>

#include "mmu.hpp"
#include "cpu.hpp"
#include "registers.hpp"
#include "instructions.hpp"
#include "interrupt.hpp"
#include "timer.hpp"

void CheckSerialPort(std::shared_ptr<MMU> mmu) {
  if (mmu->ReadByte(0xFF02) == 0x81) {
    char c = mmu->ReadByte(0xFF01);
    printf("%c", c);
    mmu->WriteByte(0xFF02, 0x0);
  }
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Arguments error" << std::endl;
    return 1;
  }

  auto registers = std::make_shared<Registers>();
  auto mmu = std::make_shared<MMU>();
  auto interrupt = std::make_shared<Interrupt>(mmu);
  auto instructions = std::make_shared<Instructions>(registers, mmu);
  auto cpu = std::make_shared<CPU>(registers, instructions, mmu, interrupt);
  auto timer = std::make_shared<Timer>(cpu, mmu, interrupt);

  mmu->LoadFile(0x0000, argv[1]);

  for (;;) {
    cpu->TickCPU();
    timer->TickTimer();
    CheckSerialPort(mmu);
  }
}