#pragma once

#include <array>
#include <cstdint>

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

class Memory {
  public:
  // Constants for memory size and program start/end addresses
  static constexpr size_t RAM_SIZE = 4096;
  static constexpr size_t PROGRAM_START = 0x200;
  static constexpr size_t PROGRAM_END = 0xFFF;

  // Constructor to initialize memory
  Memory();

  // Destructor to free memory
  ~Memory() = default;

  // Method to read a byte from memory
  uint8_t read(uint16_t address) const;

  // Method to write a byte to memory
  void write(uint16_t address, uint8_t value);

  private:
  // Array to represent memory
  std::array<uint8_t, RAM_SIZE> memory;
};
