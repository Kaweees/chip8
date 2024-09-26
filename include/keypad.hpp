#pragma once

#include <raylib.h>
#include <stddef.h>
#include <stdio.h>

#include <array>
#include <cstdint>

#include "../include/constants.hpp"
#include "rlgl.h"

// Keypad is a 4x4 matrix of keys that can be pressed
// Input Mapping:
// Keypad       Keyboard
// +-+-+-+-+    +-+-+-+-+
// |1|2|3|C|    |1|2|3|4|
// +-+-+-+-+    +-+-+-+-+
// |4|5|6|D|    |Q|W|E|R|
// +-+-+-+-+ => +-+-+-+-+
// |7|8|9|E|    |A|S|D|F|
// +-+-+-+-+    +-+-+-+-+
// |A|0|B|F|    |Z|X|C|V|
// +-+-+-+-+    +-+-+-+-+

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
