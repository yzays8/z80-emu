#pragma once

#include <cstdint>

enum Flag {
  FLAG_Z = 7,
  FLAG_N = 6,
  FLAG_H = 5,
  FLAG_C = 4,
};

class Registers {
 public:
  Registers();
  void SetZeroFlag(int res);          // z
  void SetZeroFlag(bool reset);
  void SetSubtractionFlag(bool flag); // n
  void SetHalfCarryFlag(bool flag);   // h
  void SetCarryFlag(bool flag);       // c
  bool GetFlag(Flag flag);

  struct Flags {
    uint8_t padding : 4;
    uint8_t c : 1;
    uint8_t h : 1;
    uint8_t n : 1;
    uint8_t z : 1;
  };
  static_assert(sizeof(Flags) == sizeof(uint8_t), "Flags must be 8 bits");

  union {
    struct {
      union {
        Flags flags;
        uint8_t f;
      };
      uint8_t a;
    };
    uint16_t af;
  };

  union {
    struct {
      uint8_t c;
      uint8_t b;
    };
    uint16_t bc;
  };

  union {
    struct {
      uint8_t e;
      uint8_t d;
    };
    uint16_t de;
  };

  union {
    struct {
      uint8_t l;
      uint8_t h;
    };
    uint16_t hl;
  };

  uint16_t pc, sp;
};
