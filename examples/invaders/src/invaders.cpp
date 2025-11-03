#include <stddef.h>
#include <lyra/lyra.hpp>
#include <iostream>
#include <filesystem>

#include <chip8/chip8.hpp>

namespace fs = std::filesystem;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(int argc, char** argv) {
  fs::path romfile;

  auto cli = lyra::cli() | lyra::arg(romfile, "romfile").required().help("ROM file (e.g., foo.ch8)");

  auto result = cli.parse({argc, argv});
  if (!result) {
    std::cerr << result.message() << "\n";
    return 1;
  }

  chip8::CPU chip8;
  chip8.loadRom(romfile.string());

  // Main emulation loop
  // Loop until window close button or ESC key is pressed
  while (!chip8.mapper->display.shouldClose()) { chip8.cycle(); }
  return 0;
}
