#include <raylib.h>
#include <stddef.h>
#include <stdio.h>
#include "raymath.h"
#include "rlgl.h"

#include <cstdint>
#include <cstdio>
#include <string.h>

#include "../include/cpu.hpp"
#include "../include/memory.hpp"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define PIXEL_SIZE 20

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(int argc, char **argv) {
  // Initialization of Chip8 and loading of program
  std::string file = "./rom/space-invaders.ch8";
  if (argc > 1) {
    file = argv[1];
  }

  Chip8 chip8 = Chip8();
  Memory memory = Memory();
  // (0,0)
  memory.display[0] = true;
  // (63,0)
  memory.display[63] = true;
  // (0,31)
  memory.display[64 * 31] = true;
  memory.display[64 * 32 - 1] = true;
  chip8.memory = &memory;
  // chip8.loadRom(file);

  // Initialization of Raylib
  const int screenWidth = Memory::DISPLAY_WIDTH * PIXEL_SIZE;
  const int screenHeight = Memory::DISPLAY_HEIGHT * PIXEL_SIZE;

  InitWindow(screenWidth, screenHeight, "Chip8 emulator!");

  // Main emulation loop
  // for (;;) {
  //   chip8.fetch();
  //   chip8.execute();

  //   // TODO: Implement sound and graphics
  // }

  /* Loop until window close button or ESC key is pressed */
  while (!WindowShouldClose()) {
    /* Begin drawing */
    BeginDrawing();

    /* Draw background */
    ClearBackground(BLACK);

    /* Draw screen buffer on screen */
    for (int y = 0; y < Memory::DISPLAY_HEIGHT; y++) {
      for (int x = 0; x < Memory::DISPLAY_WIDTH; x++) {
        DrawRectangle(x * PIXEL_SIZE, y * PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE, 
        chip8.memory->display[y * Memory::DISPLAY_WIDTH + x] == 1 ? WHITE : BLACK);
      }
    }
    /* End drawing */
    EndDrawing();
  }

  /* Close window and OpenGL context */
  CloseWindow();

  return EXIT_SUCCESS;
}
