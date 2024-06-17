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

// Executes the current opcode
void Chip8::execute() {
  switch (opcode & 0xF000) {
    case 0x1000:  // 0x1NNN: Jumps to address NNN
      pc = opcode & 0x0FFF;
      break;
    case 0x2000:
      // Call subroutine at NNN
      break;
    case 0x3000:
      // Skip next instruction if Vx == NN
      break;
    case 0x4000:
      // Skip next instruction if Vx != NN
      break;
    case 0x5000:
      // Skip next instruction if Vx == Vy
      break;
    case 0x6000:
      // Set Vx = NN
      break;
    case 0x7000:
      // Set Vx = Vx + NN
      break;
    case 0x8000:
      switch (opcode & 0x000F) {
        case 0x0000:
          // Set Vx = Vy
          break;
        case 0x0001:
          // Set Vx = Vx OR Vy
          break;
        case 0x0002:
          // Set Vx = Vx AND Vy
          break;
        case 0x0003:
          // Set Vx = Vx XOR Vy
          break;
        case 0x0004:
          // Set Vx = Vx + Vy, set VF = carry
          break;
        case 0x0005:
          // Set Vx = Vx - Vy, set VF = NOT borrow
          break;
        case 0x0006:
          // Set Vx = Vx SHR 1
          break;
        case 0x0007:
          // Set Vx = Vy - Vx, set VF = NOT borrow
          break;
        case 0x000E:
          // Set Vx = Vx SHL 1
          break;
        default:
          break;
      }
      break;
      // case 0x9000:
      // Skip next instruction if Vx !=
  }
}