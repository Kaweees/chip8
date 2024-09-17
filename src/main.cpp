#include <stddef.h>
#include <stdio.h>

#include <string>

#include "../include/cpu.hpp"
#include "../include/memory.hpp"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(int argc, char **argv) {
  // Initialization of Chip8 and loading of program
  std::string file = "./rom/space-invaders.ch8";
  if (argc > 1) {
    file = argv[1];
  }

  chip8::CPU chip8 = chip8::CPU();
  chip8::Memory memory = chip8::Memory();
  memory.display.setPixel(0, 0, true);
  // (63,0)
  memory.display.setPixel(63, 0, true);
  // (0,31)
  memory.display.setPixel(0, 31, true);
  // (63,31)
  memory.display.setPixel(63, 31, true);
  chip8.memory = &memory;
  // chip8.loadRom(file);

  // Main emulation loop
  // Loop until window close button or ESC key is pressed
  while (!memory.display.shouldClose()) {
    // chip8.fetch();
    // chip8.execute();
    memory.display.update();
  }
  return EXIT_SUCCESS;
}
