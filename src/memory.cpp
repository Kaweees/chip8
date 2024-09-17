#include "../include/memory.hpp"

#include <stdexcept>

namespace chip8 {
Memory::Memory() {
  // Initialize memory with 0
  ram.fill(0);
  stack.fill(0);
  keypad.fill(0);
  display.clear();
}

uint8_t Memory::fetchByte(uint16_t address) const {
  // Guard against invalid addresses
  if (PROGRAM_START <= address && address <= PROGRAM_END) {
    return ram[address];
  } else {
    throw std::out_of_range("Memory read out of bounds");
  }
}

void Memory::storeByte(uint16_t address, uint8_t value) {
  // Guard against invalid addresses
  if (PROGRAM_START <= address && address <= PROGRAM_END) {
    ram[address] = value;
  } else {
    throw std::out_of_range("Memory write out of bounds");
  }
}
}  // namespace chip8