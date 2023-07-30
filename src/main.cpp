#include <unistd.h>
#include <iostream>
#include <memory>

#include "emu.hpp"

int main(int argc, char** argv) {
  opterr = 0;
  int opt;
  bool debug_mode = false;
  bool header_mode = false;
  while ((opt = getopt(argc, argv, "dh")) != -1) {
    switch (opt) {
      case 'd':
        debug_mode = true;
        break;
      case 'h':
        header_mode = true;
        break;
      default:
        std::cerr << "Usage: " << argv[0] << " [-d] <file_path>\n"
                  << "       " << argv[0] << " [-h] <file_path>" << std::endl;
        return 1;
    }
  }

  if (optind >= argc) {
    std::cerr << "Usage: " << argv[0] << " [-d] <file_path>\n"
              << "       " << argv[0] << " [-h] <file_path>" << std::endl;
    return 1;
  }

  auto emu = std::make_unique<Emulator>();
  if (header_mode) {
    emu->LoadCartridge(argv[optind], true);
    return 0;
  }
  emu->LoadCartridge(argv[optind], false);
  emu->Run(debug_mode);
}
