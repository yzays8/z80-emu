#include <iostream>
#include <memory>

#include "emu.hpp"

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <file_path>" << std::endl;
    return 1;
  }

  auto emu = std::make_unique<Emulator>(argv[1]);
  emu->Run();
}
