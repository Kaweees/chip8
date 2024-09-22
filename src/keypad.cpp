
#include "../include/keypad.hpp"

#include <raylib.h>

#include "../include/constants.hpp"

namespace chip8 {
void Keypad::clear() {
  // Clear the keypad
  buffer.fill(false);
}

void Keypad::update() {
  // Update the keypad
  buffer[0] = IsKeyDown(KEY_ONE);
  buffer[1] = IsKeyDown(KEY_TWO);
  buffer[2] = IsKeyDown(KEY_THREE);
  buffer[3] = IsKeyDown(KEY_FOUR);
  buffer[4] = IsKeyDown(KEY_FIVE);
  buffer[5] = IsKeyDown(KEY_SIX);
  buffer[6] = IsKeyDown(KEY_SEVEN);
  buffer[7] = IsKeyDown(KEY_EIGHT);
  buffer[8] = IsKeyDown(KEY_NINE);
  buffer[9] = IsKeyDown(KEY_ZERO);
  buffer[10] = IsKeyDown(KEY_A);
  buffer[11] = IsKeyDown(KEY_B);
  buffer[12] = IsKeyDown(KEY_C);
  buffer[13] = IsKeyDown(KEY_D);
  buffer[14] = IsKeyDown(KEY_E);
  buffer[15] = IsKeyDown(KEY_F);
}

bool Keypad::getKey(uint8_t key) const { return buffer[key]; }

}  // namespace chip8