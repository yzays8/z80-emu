#pragma once

#include <memory>

#include "mmu.hpp"

class Serial {
 public:
  Serial(std::shared_ptr<MMU> mmu);
  void CheckSerialPort();

 private:
  std::shared_ptr<MMU> mmu_;
};
