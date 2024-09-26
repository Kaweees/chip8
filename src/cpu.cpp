#include "../include/cpu.hpp"

#include <fstream>
#include <iostream>

#include "../include/mapper.hpp"

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
  this->mapper = new chip8::Mapper();
  std::copy(fontset.begin(), fontset.end(), this->mapper->ram.begin());
}

void CPU::loadRom(const std::string& filename) {
  std::ifstream file(filename, std::ios::binary);
  if (file.is_open()) {
    file.read(reinterpret_cast<char*>(&mapper->ram[PROGRAM_START]),
        RAM_SIZE - PROGRAM_START);
    file.close();
  } else {
    throw std::runtime_error("Failed to open ROM file");
  }
}

// Reads a byte from the memory at the specified address
uint8_t CPU::read(uint16_t address) { return mapper->fetchByte(address); }

// Writes a byte to the memory at the specified address
void CPU::write(uint16_t address, uint8_t value) {
  if (mapper == nullptr) {
    throw std::runtime_error("Memory bus not linked to CPU");
  }
  mapper->storeByte(address, value);
}

// Executes one cycle of the CPU
void CPU::cycle() {
  // Update the keypad
  mapper->keypad.update();

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
  mapper->display.update();
}

// Fetches the next opcode from memory
void CPU::fetch() {
  opcode = read(pc) << 8 | read(pc + 1);
  std::cout << "Opcode: " << std::uppercase << std::setfill('0') << std::setw(4)
            << std::hex << opcode << std::endl;
}

// Executes the current opcode
void CPU::execute() {
  uint8_t x = (opcode & 0x0F00) >> 8;  // Extract x register
  uint8_t y = (opcode & 0x00F0) >> 4;  // Extract y register
  uint8_t n = opcode & 0x000F;         // Extract n nibble
  uint8_t nn = opcode & 0x00FF;        // Extract nn byte
  uint16_t nnn = opcode & 0x0FFF;      // Extract nnn word

  switch (opcode & 0xF000) {
    case 0x0000:
      switch (opcode) {
        case 0x00E0:  // 0x00E0: clear
          mapper->display.clear();
          pc += 2;
          break;
        case 0x00EE:  // 0x00EE: return
          pc = mapper->stack[--sp];
          pc += 2;
          break;
        default:  // 0x0NNN: call NNN
          mapper->stack[sp++] = pc;
          pc = nnn;
          break;
      }
      break;
    case 0x1000:  // 0x1NNN: jump NNN
      pc = nnn;
      break;
    case 0x2000:  // 0x2NNN: NNN
      mapper->stack[sp++] = pc;
      pc = nnn;
      break;
    case 0x3000:  // 0x3XNN: if vx != NN then
      pc += (v[x] == nn) ? 4 : 2;
      break;
    case 0x4000:  // 0x4XNN: Skips the next instruction if Vx != NN
      pc += (v[x] != nn) ? 4 : 2;
      break;
    case 0x5000:  // 0x5XY0: Skips the next instruction if Vx == Vy
      pc += (v[x] == v[y]) ? 4 : 2;
      break;
    case 0x6000:  // 0x6XNN: Sets Vx to NN
      v[x] = nn;
      pc += 2;
      break;
    case 0x7000:  // 0x7XNN: Adds NN to Vx
      v[x] += nn;
      pc += 2;
      break;
    case 0x8000:
      switch (n) {
        case 0x0:  // 0x8XY0: Sets Vx to Vy
          v[x] = v[y];
          pc += 2;
          break;
        case 0x1:  // 0x8XY1: Sets Vx to Vx OR Vy
          v[x] = v[x] | v[y];
          pc += 2;
          break;
        case 0x2:  // 0x8XY2: Sets Vx to Vx AND Vy
          v[x] = v[x] & v[y];
          pc += 2;
          break;
        case 0x3:  // 0x8XY3: Sets Vx to Vx XOR Vy
          v[x] = v[x] ^ v[y];
          pc += 2;
          break;
        case 0x4:  // 0x8XY4: Adds Vy to Vx. VF is set to 1 if there's a carry,
                   // otherwise 0
          v[0xF] = (v[x] + v[y] > 0xFF) ? 1 : 0;
          v[x] += v[y];
          pc += 2;
          break;
        case 0x5:  // 0x8XY5: Vx = Vx - Vy, VF is set to 0 if there's a borrow,
                   // otherwise 1
          v[0xF] = (v[x] > v[y]) ? 1 : 0;
          v[x] -= v[y];
          pc += 2;
          break;
        case 0x6:  // 0x8XY6: Shifts Vx right by one. VF is set to the least
                   // significant bit of Vx before the shift
          v[0xF] = v[x] & 0x1;
          v[x] >>= 1;
          pc += 2;
          break;
        case 0x7:  // 0x8XY7: Sets Vx to Vy - Vx. VF is set to 0 if there's a
                   // borrow, otherwise 1
          v[0xF] = (v[y] > v[x]) ? 1 : 0;
          v[x] = v[y] - v[x];
          pc += 2;
          break;
        case 0xE:  // 0x8XYE: Shifts Vx left by one. VF is set to the most
          // significant bit of Vx before the shift
          v[0xF] = v[x] >> 7;
          v[x] <<= 1;
          pc += 2;
          break;
        default:
          std::cout << "Unknown opcode: " << opcode << std::endl;
          break;
      }
      break;
    case 0x9000:  // 0x9XY0: Skips the next instruction if Vx != Vy
      pc += (v[x] != v[y]) ? 4 : 2;
      break;
    case 0xA000:  // 0xA000: Sets I to the address NNN
      i = nnn;
      pc += 2;
      break;
    case 0xB000:  // 0xBNNN: Jumps to the address NNN + V0
      pc = nnn + v[0];
      break;
    case 0xC000:  // 0xCXNN: Sets Vx to a random number AND NN
      v[x] = rand() & nn;
      pc += 2;
      break;
    case 0xD000: {  // 0xDXYN: Draws a sprite at (VX, VY) with a height of N
      v[0xF] = 0;
      uint8_t pixelX = v[x] % DISPLAY_WIDTH;
      uint8_t pixelY = v[y] % DISPLAY_HEIGHT;
      for (int row = 0; row < n; ++row) {
        uint8_t spriteByte = mapper->fetchByte(i + row);
        for (int col = 0; col < 8; ++col) {
          uint8_t spritePixel = (spriteByte >> (7 - col)) & 0x1;
          uint8_t displayPixel =
              mapper->display.getPixel(pixelX + col, pixelY + row);
          if (spritePixel && displayPixel) {
            v[0xF] = 1;
          }
          mapper->display.setPixel(
              pixelX + col, pixelY + row, spritePixel ^ displayPixel);
        }
      }
      pc += 2;
      break;
    }
    case 0xE000:
      switch (nn) {
        case 0x9E:  // 0xEX9E: Skips the next instruction if the key stored in
                    // Vx is pressed
          pc += (mapper->keypad.getKey(v[x])) ? 4 : 2;
          break;
        case 0xA1:  // 0xEXA1: Skips the next instruction if the key stored in
                    // Vx is not pressed
          pc += (mapper->keypad.getKey(v[x])) ? 2 : 4;
          break;
        default:
          std::cout << "Unknown opcode: " << opcode << std::endl;
          break;
      }
      break;
    case 0xF000:
      switch (nn) {
        case 0x07:  // 0xF007: Sets Vx to the value of the delay timer
          v[x] = delayTimer;
          pc += 2;
          break;
        case 0x0A:  // 0xF00A: A key press is awaited, and then stored in Vx If
                    // the same key is pressed again, the program continues as
                    // normal without waiting for the next key press
          pc += 2;
          break;
        case 0x15:  // 0xF015: Sets the delay timer to Vx
          delayTimer = v[x];
          pc += 2;
          break;
        case 0x18:  // 0xF018: Sets the sound timer to Vx
          soundTimer = v[x];
          pc += 2;
          break;
        case 0x1E:  // 0xF01E: Adds Vx to I
          i += v[x];
          pc += 2;
          break;
        case 0x29:  // 0xF029: Sets I to the location of the sprite for the
                    // character in Vx
          i = v[x] * 5;
          pc += 2;
          break;
        case 0x33:  // 0xF033: Stores the binary-coded decimal representation of
                    // Vx, with the most significant of three digits at the
                    // address in I, the middle digit at I plus 1, and the least
                    // significant digit at I plus 2
          write(i, v[x] / 100);
          write(i + 1, (v[x] / 10) % 10);
          write(i + 2, v[x] % 10);
          pc += 2;
          break;
        case 0x55:  // 0xF055: Stores V0 to VX (including VX) in memory starting
                    // at address I
          for (uint8_t j = 0; j <= x; ++j) {
            write(i + j, v[j]);
          }
          pc += 2;
          break;
        case 0x65: {  // 0xFX65: Fills V0 to VX (including VX) with values from
          // memory starting at address I
          for (; i <= x; ++i) {
            v[i] = read(i);
          }
          i += x + 1;
          pc += 2;
          break;
        }
        default:
          std::cout << "Unknown opcode: " << opcode << std::endl;
          break;
      }
      break;
    default:
      std::cout << "Unknown opcode: " << opcode << std::endl;
      break;
  }
}
}  // namespace chip8