#include <stddef.h>
#include <stdio.h>

#include <string>

#include "../include/cpu.hpp"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(int argc, char **argv) {
  // Initialization of Chip8 and loading of program
  std::string filename = "./rom/space-invaders.ch8";
  if (argc > 1) {
    filename = argv[1];
  }

  chip8::CPU chip8;
  // chip8.mapper->display.setPixel(0, 0, true);
  // // (63,0)
  // chip8.mapper->display.setPixel(63, 0, true);
  // // (0,31)
  // chip8.mapper->display.setPixel(0, 31, true);
  // // (63,31)
  // chip8.mapper->display.setPixel(63, 31, true);
  chip8.loadRom(filename);

  // Main emulation loop
  // Loop until window close button or ESC key is pressed
  while (!chip8.mapper->display.shouldClose()) {
    chip8.cycle();
  }
  return EXIT_SUCCESS;
}
