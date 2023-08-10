#pragma once

#include <memory>

#include "mmu.hpp"
#include "interrupt.hpp"

class Timer {
 public:
  Timer(std::shared_ptr<MMU> mmu, std::shared_ptr<Interrupt> interrupt);
  void Tick(int cycles);

 private:
  void IncrementDIV(int total_cycles);
  void TickTIMA(int total_cycles);

  std::shared_ptr<MMU> mmu_;
  std::shared_ptr<Interrupt> interrupt_;

  int div_counter_;
  int tima_counter_;
};
