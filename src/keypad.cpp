
#include "../include/keypad.hpp"

#include <raylib.h>

#include "../include/constants.hpp"

namespace chip8 {
void Keypad::clear() {
  // Clear the keypad
  buffer.fill(false);
}
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

void Keypad::update() {
  // Update the keypad
  buffer[0x1] = IsKeyDown(KEY_ONE);
  buffer[0x2] = IsKeyDown(KEY_TWO);
  buffer[0x3] = IsKeyDown(KEY_THREE);
  buffer[0xC] = IsKeyDown(KEY_FOUR);
  buffer[0x4] = IsKeyDown(KEY_Q);
  buffer[0x5] = IsKeyDown(KEY_W);
  buffer[0x6] = IsKeyDown(KEY_E);
  buffer[0xD] = IsKeyDown(KEY_R);
  buffer[0x7] = IsKeyDown(KEY_A);
  buffer[0x8] = IsKeyDown(KEY_S);
  buffer[0x9] = IsKeyDown(KEY_D);
  buffer[0xE] = IsKeyDown(KEY_F);
  buffer[0xA] = IsKeyDown(KEY_Z);
  buffer[0x0] = IsKeyDown(KEY_X);
  buffer[0xB] = IsKeyDown(KEY_C);
  buffer[0xF] = IsKeyDown(KEY_V);
}

bool Keypad::getKey(uint8_t key) const { return buffer[key]; }

}  // namespace chip8