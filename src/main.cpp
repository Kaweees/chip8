#include <cstdint>
#include <cstdio>

#include "../include/cpu.hpp"
#include "../include/memory.hpp"

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("Usage: %s <program>\n", argv[0]);
    return 1;
  }

  Chip8 chip8 = Chip8();
  // initialize(&chip8);
  // load_program(&chip8, argv[1]);

  // Main emulation loop
  for (;;) {
    chip8.fetch();
    chip8.execute();

    // TODO: Implement sound and graphics
  }

  return 0;
}
