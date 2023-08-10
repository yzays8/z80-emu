#include "registers.hpp"

Registers::Registers()
    : af{0x01B0}, bc{0x0013}, de{0x00D8}, hl{0x014D}, pc{0x0100}, sp{0xFFFE} {
}

void Registers::SetZeroFlag(int res) {
  flags.z = (res == 0);
}

void Registers::SetZeroFlag(bool reset) {
  if (reset) {
    flags.z = 0;
  } else {
    flags.z = 1;
  }
}

void Registers::SetSubtractionFlag(bool flag) {
  if (flag) {
    flags.n = 1;
  } else {
    flags.n = 0;
  }
}

void Registers::SetHalfCarryFlag(bool flag) {
  if (flag) {
    flags.h = 1;
  } else {
    flags.h = 0;
  }
}

void Registers::SetCarryFlag(bool flag) {
  if (flag) {
    flags.c = 1;
  } else {
    flags.c = 0;
  }
}

bool Registers::GetFlag(Flag flag) {
  return (f >> flag) & 0x1;
}
