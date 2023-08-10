#pragma once

#include <memory>

#include "mmu.hpp"

class Serial {
 public:
  Serial(std::shared_ptr<MMU> mmu);
  void CheckSerialPort(int cycles);

 private:
  std::shared_ptr<MMU> mmu_;

  int cycles_;
};
