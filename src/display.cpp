
#include "../include/display.hpp"

#include <raylib.h>

#include "../include/constants.hpp"

namespace chip8 {

Display::Display() : pixelColor(WHITE), backgroundColor(BLACK) {
  // Initialization of Raylib window
  InitWindow(DISPLAY_WIDTH * SCALE_FACTOR, DISPLAY_HEIGHT * SCALE_FACTOR,
      "CHIP-8 Emulator");
  SetTargetFPS(60);
  clear();
}

Display::~Display() {
  // Close window and OpenGL context
  CloseWindow();
}

void Display::clear() {
  for (auto& pixel : buffer) {
    pixel = false;
  }
}

void Display::setPixel(uint8_t x, uint8_t y, bool value) {
  if (x < DISPLAY_WIDTH && y < DISPLAY_HEIGHT) {
    buffer[y * DISPLAY_WIDTH + x] = value;
  }
}

bool Display::getPixel(uint8_t x, uint8_t y) const {
  if (x < DISPLAY_WIDTH && y < DISPLAY_HEIGHT) {
    return buffer[y * DISPLAY_WIDTH + x];
  }
  return false;
}

void Display::update() {
  // Begin drawing
  BeginDrawing();
  // Draw background
  ClearBackground(backgroundColor);
  // Draw screen buffer on screen
  for (int y = 0; y < DISPLAY_HEIGHT; ++y) {
    for (int x = 0; x < DISPLAY_WIDTH; ++x) {
      if (getPixel(x, y)) {
        DrawRectangle(x * SCALE_FACTOR, y * SCALE_FACTOR, SCALE_FACTOR,
            SCALE_FACTOR, pixelColor);
      }
    }
  }
  // End drawing
  EndDrawing();
}

bool Display::shouldClose() const { return WindowShouldClose(); }

}  // namespace chip8
