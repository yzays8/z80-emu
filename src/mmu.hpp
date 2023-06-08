#pragma once

#include <array>
#include <string>
#include <memory>

#include "cartridge.hpp"

class MMU {
 public:
  MMU(std::shared_ptr<Cartridge> cartridge);
  void LoadROMBank0();
  uint8_t ReadByte(uint16_t addr) const;
  uint16_t ReadShort(uint16_t addr) const;        // read 16bits
  void WriteByte(uint16_t addr, uint8_t data);
  void WriteShort(uint16_t addr, uint16_t data);  // write 16bits

 private:
  union {
    uint8_t memory_map_[0x10000];

    struct {
      union {
        uint8_t cartridge_rom_bank_0_[0x4000];
        struct {
          uint8_t restart_and_interrupt_vectors_[0x0100];
          CartridgeHeader cartridge_header_;
          uint8_t padding[0x3EB0];
        } __attribute__((packed));
      };
      uint8_t cartridge_rom_bank_n_[0x4000];
      union {
        uint8_t vram_[0x2000];
        struct {
          uint8_t character_ram_[0x1800];
          uint8_t bg_map_data1_[0x0400];
          uint8_t bg_map_data2_[0x0400];
        } __attribute__((packed));
      };
      uint8_t cartridge_ram_[0x2000];
      uint8_t internal_ram_bank_0_[0x1000];
      uint8_t internal_ram_bank_n_[0x1000];
      uint8_t echo_ram_[0x1E00];
      uint8_t oam_[0x00A0];
      uint8_t unused_[0x0060];
      uint8_t io_registers_[0x0080];
      uint8_t high_ram_[0x007F];
      uint8_t interrupt_enable_flag_;
    } __attribute__((packed));
  };

  std::shared_ptr<Cartridge> cartridge_;
};
