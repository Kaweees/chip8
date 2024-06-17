#include "../include/cpu.hpp"

#include "../include/memory.hpp"

Chip8::Chip8() {
  // Initialize the CPU
  pc = Memory::PROGRAM_START;
}

// Reads a byte from the memory at the specified address
uint8_t Chip8::read(uint16_t address) { return memory->read(address); }

// Writes a byte to the memory at the specified address
void Chip8::write(uint16_t address, uint8_t value) {
  memory->write(address, value);
}

// Fetches the next opcode from memory
void Chip8::fetch() {
  opcode = read(pc) << 8 | read(pc + 1);
  pc += 2;
}