#pragma once

#include <raylib.h>
#include <stddef.h>
#include <stdio.h>

#include <array>
#include <cstdint>

#include "../include/constants.hpp"
#include "rlgl.h"

// Keypad is a 64x32 monochrome Keypad. Each byte represents 8 pixels in a
// column.
namespace chip8 {
class Keypad {
  public:
  // Constructor to initialize memory
  Keypad() = default;

  // Destructor to free memory
  ~Keypad() = default;

  // Method to clear the keypad
  void clear();

  // Method to update the keypad
  void update();

  // Method to get the state of a key on the keypad
  bool getKey(uint8_t key) const;

  private:
  // Array to represent keypad
  std::array<bool, KEYPAD_SIZE> buffer;  // 16 keys
};
}  // namespace chip8
