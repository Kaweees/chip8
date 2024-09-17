#pragma once
#include <cstddef>

namespace chip8 {
// Constants for display size and scale factor in pixels
constexpr int DISPLAY_WIDTH = 64;
constexpr int DISPLAY_HEIGHT = 32;
constexpr int SCALE_FACTOR = 20;

// Constants for memory size
constexpr size_t KILOBYTE = 1024;
constexpr size_t RAM_SIZE = 4 * KILOBYTE;
constexpr size_t STACK_SIZE = 16;
constexpr size_t KEYPAD_SIZE = 16;
// Constants for program addresses
constexpr size_t PROGRAM_START = 0x200;
constexpr size_t PROGRAM_END = 0xFFF;
}  // namespace chip8
