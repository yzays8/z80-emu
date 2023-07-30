#include <iostream>
#include <fstream>
#include <array>
#include <memory>
#include <vector>
#include <filesystem>
#include <string>

#include "cartridge.hpp"

Cartridge::Cartridge()
    : rom_{},
      ram_{},
      header_{},
      cartridge_type_{NO_MBC},
      current_rom_bank_{0},
      current_ram_bank_{0},
      banking_mode_{ROM_MODE} {}

void Cartridge::Load(const std::string& path, bool only_header) {
  LoadROM(path);
  PrintHeader();
  if (only_header) {
    VerifyHeaderChecksum();
    return;
  }

  switch (header_->cartridge_type) {
    case 0x0:
      cartridge_type_ = NO_MBC;
      break;
    case 0x1:
    case 0x2:
    case 0x3:
      cartridge_type_ = MBC1;
      break;
    default:
      std::cerr << "Invalid cartridge type: " << header_->cartridge_type << std::endl;
      std::exit(EXIT_FAILURE);
  }
  current_rom_bank_ = 1;
  current_ram_bank_ = 0;
}

void Cartridge::LoadROM(const std::string& path) {
  if (!std::filesystem::is_regular_file(path)) {
    std::cerr << path << " is not a regular file" << std::endl;
    std::exit(EXIT_FAILURE);
  }
  std::ifstream ifs(path, std::ios::binary | std::ios::in);
  if (!ifs.is_open()) {
    std::cerr << "Failed to open file: " << path << std::endl;
    std::exit(EXIT_FAILURE);
  }

  char data;
  for (int i = 0; i < 0x100; ++i) {
    ifs.get(data);
    rom_.push_back(static_cast<uint8_t>(data));
  }

  // load header
  uint8_t tmp[0x50];
  for (int i = 0; i < 0x50; ++i) {
    ifs.get(data);
    tmp[i] = static_cast<uint8_t>(data);
    rom_.push_back(static_cast<uint8_t>(data));
  }
  header_ = std::make_unique<CartridgeHeader>(*reinterpret_cast<CartridgeHeader*>(tmp));

  while (ifs.get(data)) {
    rom_.push_back(static_cast<uint8_t>(data));
  }

  std::cout << "Loaded ROM" << std::endl;
}

void Cartridge::PrintHeader() {
  printf("Title: %s\nCartridge type: %d\nROM size: %dKiB\n",
    header_->title_new, header_->cartridge_type, 32 * (1 << header_->rom_size));
}

void Cartridge::VerifyHeaderChecksum() {
  uint8_t calculated_checksum = 0;
  for (uint16_t addr = 0x0134; addr <= 0x014C; ++addr) {
    calculated_checksum -= rom_[addr] + 1;
  }
  if (calculated_checksum != header_->header_checksum) {
    std::cerr << "Invalid header checksum\n"
              << "Calculated: " << calculated_checksum << '\n'
              << "Expected: " << header_->header_checksum << std::endl;
    std::exit(EXIT_FAILURE);
  }
  std::cout << "Valid header checksum" << std::endl;
}

void Cartridge::VerifyGlobalChecksum() {
  uint16_t checksum = 0;
  for (uint16_t addr = 0x0000; addr < 0x014E; ++addr) {
    checksum += rom_[addr];
  }
  for (size_t addr = 0x0150; addr < rom_.size(); ++addr) {
    checksum += rom_[addr];
  }
  uint16_t expected_checksum = (header_->global_checksum[0] << 8) | header_->global_checksum[1];
  if (checksum != expected_checksum) {
    std::cerr << "Invalid global checksum\n"
              << "Calculated: " << checksum << '\n'
              << "Expected: " << expected_checksum << std::endl;
    std::exit(EXIT_FAILURE);
  }
  std::cout << "Valid global checksum" << std::endl;
}

uint8_t Cartridge::ReadByteFromROM(uint16_t addr) const {
  return rom_[addr];
}

uint8_t Cartridge::ReadByteFromRAM(uint16_t addr) const {
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
