#pragma once
#include <cstdint>
#include <map>
#include <string>
#include <vector>

#ifdef LOGMODE
#include <cstdio>
#endif

// Forward declaration of generic communications bus class to
// prevent circular inclusions
class Memory;

// The meat and potatoes - a class representing the emulated Chip-8 CPU
class Chip8 {
  public:
  // Constructor to initialize memory
  Chip8();

  // Destructor to free memory
  ~Chip8() = default;

  public:
  uint8_t v[16] = {0};   // General Purpose Registers (V0-VF)
  uint16_t i = 0;        // I - stores memory addresses
  uint8_t dt = 0;        // Delay Timer
  uint8_t st = 0;        // Sound Timer
  uint16_t pc = 0x0000;  // Program Counter - stores address of next instruction
                         // to execute
  uint8_t sp = 0x00;     // Stack Pointer - points to location on memory bus

  // Assisstive variables to facilitate emulation
  uint16_t opcode = 0x0000;  // The current opcode being executed

  // Linkage to the memory bus
  Memory *memory = nullptr;
  uint8_t read(uint16_t a);
  void write(uint16_t a, uint8_t d);

#ifdef LOGMODE
  private:
  FILE *logfile = nullptr;
#endif
};
