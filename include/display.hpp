#pragma once

#include <stddef.h>
#include <stdio.h>

#include <array>
#include <cstdint>

#include "../include/constants.hpp"

// Display is a 64x32 monochrome display. Each byte represents 8 pixels in a
// column.
// (0,0)	(63,0)
// (0,31)	(63,31)
namespace chip8 {
class Display {
  public:
  // Constants for display screen size
  static constexpr size_t SCREEN_WIDTH = DISPLAY_WIDTH * PIXEL_SIZE;
  static constexpr size_t SCREEN_HEIGHT = DISPLAY_HEIGHT * PIXEL_SIZE;

  // Constructor to initialize memory
  Display();

  // Destructor to free memory
  ~Display() = default;

  // Method to clear the display
  void clear();

  // Method to set a pixel on the display
  void setPixel(uint8_t x, uint8_t y);

  // Method to get the state of a pixel on the display
  bool getPixel(uint8_t x, uint8_t y) const;

  private:
  // Array to represent display
  std::array<bool, DISPLAY_WIDTH * DISPLAY_HEIGHT>
      buffer;  // monochrome display
};
}  // namespace chip8
