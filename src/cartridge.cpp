#include <iostream>
#include <fstream>
#include <array>

#include "cartridge.hpp"

Cartridge::Cartridge(std::string path) : rom_{}, ram_{0}, banking_mode_{ROM_MODE} {
  LoadROM(path);
  switch (rom_[0x147]) {
    case 0x0:
      cartridge_type_ = NO_MBC;
      break;
    case 0x1:
    case 0x2:
    case 0x3:
      cartridge_type_ = MBC1;
      break;
    default:
      std::cerr << "Invalid cartridge type: " << rom_[0x147] << std::endl;
      std::exit(EXIT_FAILURE);
  }
  current_rom_bank_ = 1;
  current_ram_bank_ = 0;
}

void Cartridge::LoadROM(std::string path) {
  std::ifstream ifs(path, std::ios::binary | std::ios::in);
  if (!ifs.is_open()) {
    std::cerr << "Failed to open file" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  char data;
  for (int i = 0; ifs.get(data); ++i) {
    rom_.push_back(static_cast<uint8_t>(data));
  }
  std::cout << "Loaded ROM" << std::endl;
}

uint8_t Cartridge::ReadByteFromROM(uint16_t addr) {
  return rom_[addr];
}

uint8_t Cartridge::ReadByteFromRAM(uint16_t addr) {
  return ram_[addr];
}

void Cartridge::WriteByteToRAM(uint16_t addr, uint8_t data) {
  ram_[addr] = data;
}

uint8_t Cartridge::GetCurrentROMBank() const {
  return current_rom_bank_;
}

void Cartridge::SetCurrentROMBank(uint8_t bank) {
  current_rom_bank_ = bank;
}

uint8_t Cartridge::GetCurrentRAMBank() const {
  return current_ram_bank_;
}

void Cartridge::SetCurrentRAMBank(uint8_t bank) {
  current_ram_bank_ = bank;
}

CartridgeType Cartridge::GetCartridgeType() const {
  return cartridge_type_;
}

void Cartridge::ChangeBankingMode(uint8_t data) {
  uint8_t reg = data & 0x1;
  if (reg == 0) {
    banking_mode_ = ROM_MODE;
  } else if (reg == 1) {
    banking_mode_ = RAM_MODE;
  }

  if (banking_mode_ == ROM_MODE) {
    current_ram_bank_ = 0;
  }
}

BankingMode Cartridge::GetBankingMode() const {
  return banking_mode_;
}
