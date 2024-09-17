#include "../include/cpu.hpp"

#include <fstream>
#include <iostream>

#include "../include/memory.hpp"

namespace chip8 {
CPU::CPU() {
  // Initialize the CPU
  pc = PROGRAM_START;

  // Load fontset
  static const std::array<uint8_t, 80> fontset = {
      0xF0, 0x90, 0x90, 0x90, 0xF0,  // 0
      0x20, 0x60, 0x20, 0x20, 0x70,  // 1
      0xF0, 0x10, 0xF0, 0x80, 0xF0,  // 2
      0xF0, 0x10, 0xF0, 0x10, 0xF0,  // 3
      0x90, 0x90, 0xF0, 0x10, 0x10,  // 4
      0xF0, 0x80, 0xF0, 0x10, 0xF0,  // 5
      0xF0, 0x80, 0xF0, 0x90, 0xF0,  // 6
      0xF0, 0x10, 0x20, 0x40, 0x40,  // 7
      0xF0, 0x90, 0xF0, 0x90, 0xF0,  // 8
      0xF0, 0x90, 0xF0, 0x10, 0xF0,  // 9
      0xF0, 0x90, 0xF0, 0x90, 0x90,  // A
      0xE0, 0x90, 0xE0, 0x90, 0xE0,  // B
      0xF0, 0x80, 0x80, 0x80, 0xF0,  // C
      0xE0, 0x90, 0x90, 0x90, 0xE0,  // D
      0xF0, 0x80, 0xF0, 0x80, 0xF0,  // E
      0xF0, 0x80, 0xF0, 0x80, 0x80   // F
  };
  this->memory = new chip8::Memory();
  std::copy(fontset.begin(), fontset.end(), this->memory->ram.begin());
}

void CPU::loadRom(const std::string& file) {
  std::ifstream rom(file, std::ios::binary);
  if (!rom) {
    throw std::runtime_error("Failed to open ROM file");
  }
  rom.read(reinterpret_cast<char*>(memory->ram.data() + PROGRAM_START),
      memory->ram.size() - PROGRAM_START);
}

// Reads a byte from the memory at the specified address
uint8_t CPU::read(uint16_t address) { return memory->fetchByte(address); }

// Writes a byte to the memory at the specified address
void CPU::write(uint16_t address, uint8_t value) {
  if (memory == nullptr) {
    throw std::runtime_error("Memory bus not linked to CPU");
  }
  memory->storeByte(address, value);
}

// Executes one cycle of the CPU
void CPU::cycle() {
  fetch();
  execute();

  // Update timers
  if (delayTimer > 0) {
    --delayTimer;
  }
  if (soundTimer > 0) {
    --soundTimer;
  }

  // Update the display
  memory->display.update();
}

// Fetches the next opcode from memory
void CPU::fetch() {
  opcode = read(pc) << 8 | read(pc + 1);
  std::cout << "Opcode: " << opcode << std::endl;
  pc += 2;
}

// Executes the current opcode
void CPU::execute() {
  switch (opcode & 0xF000) {
    case 0x1000:  // 0x1NNN: Jumps to address NNN
      pc = opcode & 0x0FFF;
      break;
    // case 0x2000:
    //   // Call subroutine at NNN
    //   break;
    // case 0x3000:
    //   // Skip next instruction if Vx == NN
    //   break;
    // case 0x4000:
    //   // Skip next instruction if Vx != NN
    //   break;
    // case 0x5000:
    //   // Skip next instruction if Vx == Vy
    //   break;
    // case 0x6000:
    //   // Set Vx = NN
    //   break;
    // case 0x7000:
    //   // Set Vx = Vx + NN
    //   break;
    // case 0x8000:
    //   switch (opcode & 0x000F) {
    //     case 0x0000:
    //       // Set Vx = Vy
    //       break;
    //     case 0x0001:
    //       // Set Vx = Vx OR Vy
    //       break;
    //     case 0x0002:
    //       // Set Vx = Vx AND Vy
    //       break;
    //     case 0x0003:
    //       // Set Vx = Vx XOR Vy
    //       break;
    //     case 0x0004:
    //       // Set Vx = Vx + Vy, set VF = carry
    //       break;
    //     case 0x0005:
    //       // Set Vx = Vx - Vy, set VF = NOT borrow
    //       break;
    //     case 0x0006:
    //       // Set Vx = Vx SHR 1
    //       break;
    //     case 0x0007:
    //       // Set Vx = Vy - Vx, set VF = NOT borrow
    //       break;
    //     case 0x000E:
    //       // Set Vx = Vx SHL 1
    //       break;
    //     default:
    //       break;
    //   }
    //   break;
    // case 0x9000:
    //   // Skip next instruction if Vx != Vy
    //   break;
    // case 0xA000:
    //   // Set I = NNN
    //   break;
    // case 0xB000:
    //   // Jump to location NNN + V0
    //   break;
    // case 0xC000:
    //   // Set Vx = random byte AND NN
    //   break;
    // case 0xD000:
    //   // Display n-byte sprite starting at memory location I at (Vx, Vy), set
    //   VF
    //   // = collision
    //   break;
    // case 0xE000:
    //   switch (opcode & 0x00FF) {
    //     case 0x009E:
    //       // Skip next instruction if key with the value of Vx is pressed
    //       break;
    //     case 0x00A1:
    //       // Skip next instruction if key with the value of Vx is not pressed
    //       break;
    //     default:
    //       break;
    //   }
    //   break;
    // case 0xF000:
    //   switch (opcode & 0x00FF) {
    //     case 0x0007:
    //       // Set Vx = delay timer value
    //       break;
    //     case 0x000A:
    //       // Wait for a key press, store the value of the key in Vx
    //       break;
    //     case 0x0015:
    //       // Set delay timer = Vx
    //       break;
    //     case 0x0018:
    //       // Set sound timer = Vx
    //       break;
    //     case 0x001E:
    //       // Set I = I + Vx
    //       break;
    //     case 0x0029:
    //       // Set I = location of sprite for digit Vx
    //       break;
    //     case 0x0033:
    //       // Store BCD representation of Vx in memory locations I, I+1, and
    //       I+2 break;
    //     case 0x0055:
    //       // Store registers V0 through Vx in memory starting at location I
    //       break;
    //     case 0x0065:
    //       // Read registers V0 through Vx from memory starting at location I
    //       break;
    //     default:
    //       break;
    //   }
    //   break;
    default:
      std::cout << "Unknown opcode: " << opcode << std::endl;
      break;
  }
}
}  // namespace chip8