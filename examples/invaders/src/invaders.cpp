#include <stddef.h>
#include <stdio.h>

#include <string>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#include <chip8/chip8.hpp>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(int argc, char** argv) {
  // Initialization of Chip8 and loading of program
  std::string filename = "./rom/space-invaders.ch8";
  if (argc > 1) { filename = argv[1]; }

  chip8::CPU chip8;
  chip8.loadRom(filename);

  // Main emulation loop
  // Loop until window close button or ESC key is pressed
  while (!chip8.mapper->display.shouldClose()) { chip8.cycle(); }
  return EXIT_SUCCESS;
}
