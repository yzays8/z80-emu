#pragma once

#include <array>
#include <string>
#include <memory>

#include "cartridge.hpp"

class MMU {
 public:
  MMU(std::shared_ptr<Cartridge> cartridge);
  void LoadROMBank0();
  uint8_t ReadByte(const uint16_t addr) const;
  uint16_t ReadShort(const uint16_t addr) const;  // read 16bits
  void WriteByte(uint16_t addr, uint8_t data);
  void WriteShort(uint16_t addr, uint16_t data);  // write 16bits

 private:
  std::array<uint8_t, 0x10000> memory_map_;

  std::shared_ptr<Cartridge> cartridge_;
};
