#pragma once

#include <memory>

#include "cpu.hpp"
#include "interrupt.hpp"

class Timer {
 public:
  Timer(std::shared_ptr<CPU> cpu, std::shared_ptr<MMU> mmu, std::shared_ptr<Interrupt> interrupt);
  void Tick();

 private:
  void IncrementDIV(int total_cycles);
  void TickTIMA(int total_cycles);

  std::shared_ptr<CPU> cpu_;
  std::shared_ptr<MMU> mmu_;
  std::shared_ptr<Interrupt> interrupt_;

  int div_counter_, tima_counter_;
};
