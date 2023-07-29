#pragma once

#include <cstdint>
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

struct CartridgeHeader {
  uint8_t entry_point[4];
  uint8_t logo[48];
  union {
    uint8_t title_old[16];
    struct {
      uint8_t title_new[11];
      uint8_t manufacturer_code[4];
      uint8_t cgb_flag;
    } __attribute__((packed));
  };
  uint8_t new_licensee_code[2];
  uint8_t sgb_flag;
  uint8_t cartridge_type;
  uint8_t rom_size;
  uint8_t ram_size;
  uint8_t destination_code;
  uint8_t old_licensee_code;
  uint8_t mask_rom_version_number;
  uint8_t header_checksum;
  uint8_t global_checksum[2];
} __attribute__((packed));

class Cartridge {
 public:
  Cartridge(std::string path);

  void LoadROM(std::string path);
  uint8_t ReadByteFromROM(uint16_t addr) const;
  uint8_t ReadByteFromRAM(uint16_t addr) const;
  void WriteByteToRAM(uint16_t addr, uint8_t data);

  uint8_t GetCurrentROMBank() const;
  void SetCurrentROMBank(uint8_t bank);
  uint8_t GetCurrentRAMBank() const;
  void SetCurrentRAMBank(uint8_t bank);

  CartridgeType GetCartridgeType() const;
  void ChangeBankingMode(uint8_t data);
  BankingMode GetBankingMode() const;

  void PrintHeader();

  // this verification will be automatically done by the emulator
  void VerifyHeaderChecksum();
  // this verification is not normally done
  void VerifyGlobalChecksum();

  bool ram_enabled{false};

 private:
  std::vector<uint8_t> rom_;
  std::array<uint8_t, 0x8000> ram_;
  std::unique_ptr<CartridgeHeader> header_;

  CartridgeType cartridge_type_;
  uint8_t current_rom_bank_;
  uint8_t current_ram_bank_;
  BankingMode banking_mode_;
};
