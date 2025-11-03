#pragma once

#include <array>
#include <cstdint>
#include <iostream>
#include "display.hpp"
#include "keypad.hpp"

#include <stdexcept>

// Memory Map:
// +---------------+= 0xFFF (4095) End of Chip-8 RAM
// |               |
// |               |
// |               |
// |               |
// |               |
// | 0x200 to 0xFFF|
// |     Chip-8    |
// | Program / Data|
// |     Space     |
// |               |
// |               |
// |               |
// +- - - - - - - -+= 0x600 (1536) Start of ETI 660 Chip-8 programs
// |               |
// |               |
// |               |
// +---------------+= 0x200 (512) Start of most Chip-8 programs
// | 0x000 to 0x1FF|
// | Reserved for  |
// |  interpreter  |
// +---------------+= 0x000 (0) Start of Chip-8 RAM

// The mapper is responsible for mapping the various memory buses to the
// emulated Chip-8 system.

namespace chip8 {
class Mapper {
  public:
    // Constructor to initialize memory
    Mapper() {
      // Initialize memory with 0
      ram.fill(0);
      stack.fill(0);
      keypad.clear();
      display.clear();
    }

    // Destructor to free memory
    ~Mapper() = default;

    // Method to read a byte from memory
    uint8_t fetchByte(uint16_t address) const {
      // Guard against invalid addresses
      if (PROGRAM_START <= address && address <= PROGRAM_END) {
        return ram[address];
      } else {
        throw std::out_of_range("Memory read out of bounds");
      }
    }

    // Method to write a byte to memory
    void storeByte(uint16_t address, uint8_t value) {
      // Guard against invalid addresses
      if (PROGRAM_START <= address && address <= PROGRAM_END) {
        ram[address] = value;
      } else {
        throw std::out_of_range("Memory write out of bounds");
      }
    }

    // Method to print memory
    void printMemory() const {
      for (int i = 0; i < RAM_SIZE; i++) { std::cout << "Memory[" << i << "] = " << ram[i] << std::endl; }
    }

    // Array to represent memory
    std::array<uint8_t, RAM_SIZE> ram; // 4 kB of memory
    // Array to represent stack
    std::array<uint16_t, STACK_SIZE> stack; // 16 levels of stack
    // Array to represent keypad
    Keypad keypad;
    // Array to represent display
    Display display;
};
} // namespace chip8
