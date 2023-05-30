#pragma once

#include <string>
#include <array>
#include <vector>
#include <memory>

enum CartridgeType {
  NO_MBC,
  MBC1,
  MBC2,
};

enum BankingMode {
  ROM_MODE,
  RAM_MODE,
};

class Cartridge {
 public:
  Cartridge(std::string path);

  void LoadROM(std::string path);
  uint8_t ReadByteFromROM(uint16_t addr);
  uint8_t ReadByteFromRAM(uint16_t addr);
  void WriteByteToRAM(uint16_t addr, uint8_t data);
  uint8_t GetCurrentROMBank() const;
  void SetCurrentROMBank(uint8_t bank);
  uint8_t GetCurrentRAMBank() const;
  void SetCurrentRAMBank(uint8_t bank);
  CartridgeType GetCartridgeType() const;
  void ChangeBankingMode(uint8_t data);
  BankingMode GetBankingMode() const;

  bool ram_enabled{false};

 private:
  std::vector<uint8_t> rom_;
  std::array<uint8_t, 0x8000> ram_;

  CartridgeType cartridge_type_;
  uint8_t current_rom_bank_;
  uint8_t current_ram_bank_;
  BankingMode banking_mode_;
};
