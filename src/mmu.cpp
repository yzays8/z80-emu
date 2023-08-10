#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>

#include "mmu.hpp"
#include "cartridge.hpp"

MMU::MMU() : memory_map_{}, cartridge_{std::make_unique<Cartridge>()} {
  std::memset(memory_map_, 0, sizeof(memory_map_));
}

void MMU::LoadROMBank0() {
  for (int i = 0; i < 0x4000; ++i) {
    cartridge_rom_bank_0_[i] = cartridge_->ReadByteFromROM(i);
  }
}

void MMU::LoadCartridge(const std::string& path, bool only_header) {
  cartridge_->Load(path, only_header);
  if (!only_header) {
    LoadROMBank0();
  }
}

uint8_t MMU::ReadByte(uint16_t addr) const {
  // read from switchable 16KiB ROM bank
  if (addr >= 0x4000 && addr < 0x8000) {
    return cartridge_->ReadByteFromROM(addr - 0x4000 + 0x4000 * cartridge_->GetCurrentROMBank());
  }

  // read from cartridge RAM bank
  if (addr >= 0xA000 && addr < 0xC000) {
    if (cartridge_->ram_enabled) {
      return cartridge_->ReadByteFromRAM(addr - 0xA000 + 0x2000 * cartridge_->GetCurrentRAMBank()); // each RAM size is 0x2000 = 8KiB
    }
    return 0xFF;
  }

  return memory_map_[addr];
}

uint16_t MMU::ReadShort(uint16_t addr) const {
  // the value of higher address is higher bits
  return ReadByte(addr) | (ReadByte(addr + 1) << 8);
}

void MMU::WriteByte(uint16_t addr, uint8_t data) {
  if (addr < 0x2000) {
    // enable or disable RAM
    uint8_t nibble = data & 0xF;
    if (nibble == 0xA) {
      cartridge_->ram_enabled = true;
    } else if (nibble == 0x0) {
      cartridge_->ram_enabled = false;
    }
  } else if (addr < 0x4000) {
    // select ROM bank, 1
    uint8_t reg = data & 0b11111;
    cartridge_->SetCurrentROMBank((cartridge_->GetCurrentROMBank() & 0b1110'0000) | reg);
    if (reg == 0) {
      cartridge_->SetCurrentROMBank((cartridge_->GetCurrentROMBank() & 0b1110'0000) | 0b1);
    }
  } else if (addr < 0x6000) {
    if (cartridge_->GetBankingMode() == ROM_MODE) {
      // select ROM bank, 2
      cartridge_->SetCurrentROMBank((cartridge_->GetCurrentROMBank() & 0b1001'1111) | ((data & 0b11) << 5));
    } else if (cartridge_->GetBankingMode() == RAM_MODE) {
      // select RAM bank
      cartridge_->SetCurrentRAMBank(data & 0b11);
    }
  } else if (addr < 0x8000) {
    // select banking mode
    cartridge_->ChangeBankingMode(data);
  } else if (addr >= 0xA000 && addr < 0xC000) {
    if (cartridge_->ram_enabled) {
      cartridge_->WriteByteToRAM(addr - 0xA000 + 0x2000 * cartridge_->GetCurrentRAMBank(), data);
    }
  } else if (addr == 0xFF04) {
    memory_map_[addr] = 0;
  } else {
    memory_map_[addr] = data;
  }
}

void MMU::WriteShort(uint16_t addr, uint16_t data) {
  WriteByte(addr, data & 0xFF);
  WriteByte(addr + 1, (data >> 8) & 0xFF);
}
