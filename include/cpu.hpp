#pragma once
#include <cstdint>
#include <random>
#include <string>

#include "../include/mapper.hpp"

#ifdef LOGMODE
#include <cstdio>
#endif

namespace chip8 {
// The meat and potatoes - a class representing the emulated Chip-8 CPU
class CPU {
  public:
    // Constructor to initialize memory
    CPU();

    // Destructor to free memory
    ~CPU() = default;
  private:
    uint8_t v[16] = {0}; // General Purpose Registers (V0-VF)
    uint16_t i = 0; // I - stores memory addresses
    uint8_t dt = 0; // Delay Timer
    uint8_t st = 0; // Sound Timer
    uint16_t pc = 0x0000; // Program Counter - stores address of next instruction
                          // to execute
    uint8_t sp = 0x00; // Stack Pointer - points to location on memory bus
    uint8_t delayTimer;
    uint8_t soundTimer;
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_int_distribution<> dis;
    std::chrono::nanoseconds frameDuration;
    std::chrono::steady_clock::time_point lastCycleTime;
#ifdef LOGMODE
    FILE* logfile = nullptr; // Log file for debugging
#endif

    // Assisstive variables to facilitate emulation
    uint16_t opcode = 0x0000; // The current opcode being executed
  public:
    // Linkage to the memory bus
    Mapper* mapper = nullptr;

    uint8_t read(uint16_t address);
    void write(uint16_t address, uint8_t value);

    // Method to load a ROM into memory
    void loadRom(const std::string& filename);

    // Executes one cycle of the CPU
    void cycle();

    // Fetches the next opcode from memory
    void fetch();

    // Executes the current opcode
    void execute();
};
} // namespace chip8
