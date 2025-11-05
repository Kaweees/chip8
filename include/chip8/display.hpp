#pragma once

#include <raylib.h>
#include <stddef.h>
#include <stdio.h>

#include <array>
#include <cstdint>

#include "constants.hpp"
#include "rlgl.h"
#include <raylib.h>

// Display is a 64x32 monochrome display. Each byte represents 8 pixels in a
// column.
// (0,0)	(63,0)
// (0,31)	(63,31)
namespace chip8 {
class Display {
  public:
    // Constants for display screen size
    static constexpr size_t SCREEN_WIDTH = chip8::DISPLAY_WIDTH * chip8::SCALE_FACTOR;
    static constexpr size_t SCREEN_HEIGHT = chip8::DISPLAY_HEIGHT * chip8::SCALE_FACTOR;

    // Constructor to initialize memory
    Display()
      : pixelColor(WHITE),
        backgroundColor(BLACK) {
      // Initialization of Raylib window
      InitWindow(DISPLAY_WIDTH * SCALE_FACTOR, DISPLAY_HEIGHT * SCALE_FACTOR, "CHIP-8 Emulator");
      clear();
    }

    // Destructor to free memory
    ~Display() {
      // Close window and OpenGL context
      CloseWindow();
    }

    // Method to clear the display
    void clear() {
      for (auto& pixel : buffer) { pixel = false; }
    }

    // Method to set a pixel on the display
    void setPixel(uint8_t x, uint8_t y, bool value) {
      if (x < DISPLAY_WIDTH && y < DISPLAY_HEIGHT) { buffer[y * DISPLAY_WIDTH + x] = value; }
    }

    // Method to get the state of a pixel on the display
    bool getPixel(uint8_t x, uint8_t y) const {
      if (x < DISPLAY_WIDTH && y < DISPLAY_HEIGHT) { return buffer[y * DISPLAY_WIDTH + x]; }
      return false;
    }

    // Method to update the display
    void update() {
      // Begin drawing
      BeginDrawing();
      // Draw background
      ClearBackground(backgroundColor);
      // Draw screen buffer on screen
      for (int y = 0; y < DISPLAY_HEIGHT; ++y) {
        for (int x = 0; x < DISPLAY_WIDTH; ++x) {
          if (getPixel(x, y)) {
            DrawRectangle(x * SCALE_FACTOR, y * SCALE_FACTOR, SCALE_FACTOR, SCALE_FACTOR, pixelColor);
          }
        }
      }
      // End drawing
      EndDrawing();
    }

    // Method to check if the display should close
    bool shouldClose() const { return WindowShouldClose(); }
  private:
    // Array to represent display
    std::array<bool, DISPLAY_WIDTH * DISPLAY_HEIGHT> buffer; // monochrome display
    Color pixelColor;
    Color backgroundColor;
};
} // namespace chip8
