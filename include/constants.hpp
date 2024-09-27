#pragma once
#include <chrono>
#include <cstddef>
using namespace std::chrono_literals;

namespace chip8 {
// Constants for game speed
constexpr int TARGET_FPS = 60;  // Target frames per second
constexpr auto FRAME_DURATION =
    std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::seconds(1)) /
    TARGET_FPS;  // Duration of a frame in nanoseconds
constexpr int INSTRUCTIONS_PER_FRAME = 10;

// Constants for display size and scale factor in pixels
constexpr int DISPLAY_WIDTH = 64;
constexpr int DISPLAY_HEIGHT = 32;
constexpr int SCALE_FACTOR = 20;
constexpr int CYCLE_DELAY = 3;

// Constants for memory size
constexpr size_t KILOBYTE = 1024;
constexpr size_t RAM_SIZE = 4 * KILOBYTE;
constexpr size_t STACK_SIZE = 16;
constexpr size_t KEYPAD_SIZE = 16;
// Constants for program addresses
constexpr size_t PROGRAM_START = 0x200;
constexpr size_t PROGRAM_END = 0xFFF;

// Constants for fontset
constexpr size_t FONTSET_START = 0x000;
constexpr size_t FONTSET_END = 0x1FF;
}  // namespace chip8
