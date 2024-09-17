#include "../include/memory.hpp"

#include <stdexcept>

namespace chip8 {
Memory::Memory() {
  // Initialize memory with 0
  memory.fill(0);
  stack.fill(0);
  keypad.fill(0);
  display.clear();
}

uint8_t Memory::read(uint16_t address) const {
  // Guard to check if address is within memory bounds
  if (Memory::PROGRAM_START <= address && address <= Memory::PROGRAM_START) {
    return memory[address];
  } else {
    throw std::out_of_range("Memory read out of bounds");
  }
}

void Memory::write(uint16_t address, uint8_t value) {
  // Guard to check if address is within memory bounds
  if (Memory::PROGRAM_START <= address && address <= Memory::PROGRAM_START) {
    memory[address] = value;
  } else {
    throw std::out_of_range("Memory write out of bounds");
  }
}
}  // namespace chip8