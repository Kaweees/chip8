#include "../include/memory.hpp"

#include <stdexcept>

Memory::Memory() {
  // Initialize memory with 0
  memory.fill(0);
}

uint8_t Memory::read(uint16_t address) const {
  static constexpr size_t RAM_START = 0x200;
  static constexpr size_t RAM_END = 0xFFF;
  // Guard to check if address is within memory bounds
  if (RAM_START <= address && address <= RAM_END) {
    return memory[address];
  } else {
    throw std::out_of_range("Memory read out of bounds");
  }
}