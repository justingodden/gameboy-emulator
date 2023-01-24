#pragma once

#include <array>
#include <stdint.h>
#include "Bus.h"
#include "Interrupts.h"

class Bus;
class Interrupts;

class Ppu
{
public:
    Ppu();
    ~Ppu();

public:
    uint8_t readVRamByte(uint16_t addr) const;
    void writeVRamByte(uint16_t addr, uint8_t data);

    uint8_t readLcdByte(uint16_t addr) const;
    void writeLcdByte(uint16_t addr, uint8_t data);

    void update(unsigned int cycles);

    void setBus(Bus *bus);
    void setInterrupts(Interrupts *interrupts);

private:
    void dmaTranser(uint8_t data);
    bool lcdEnabled();
    void setLcdStatus();

private:
    std::array<uint8_t, 0x2000> vRam;
    std::array<std::array<std::array<uint8_t, 160>, 144>, 3> screenData;
    uint8_t lcdControl = 0;      // 0xFF40
    uint8_t lcdStatus = 0;       // 0xFF41
    uint8_t currentScanline = 0; // 0xFF44 (LY)
    uint8_t LYC = 0;             // 0xFF45 (current scanline compare (if LY == LYC, set flag in stat register))
    uint16_t scalineCounter = 0;

    Bus *bus = nullptr;
    Interrupts *interrupts = nullptr;
};