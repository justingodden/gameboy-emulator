#pragma once

#include <array>
#include <stdint.h>
#include "Bus.h"
#include "Interrupts.h"

class Bus;
class Interrupts;

enum COLOUR
{
    WHITE,
    LIGHT_GRAY,
    DARK_GRAY,
    BLACK
};

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
    void drawScanline();
    void renderTiles();
    void renderSprites();
    COLOUR getColour(uint8_t num, uint16_t addr);

private:
    std::array<uint8_t, 0x2000> vRam;
    std::array<uint8_t, 160 * 144 * 4> screenData;
    uint8_t lcdControl = 0;      // 0xFF40
    uint8_t lcdStatus = 0;       // 0xFF41
    uint8_t currentScanline = 0; // 0xFF44 (LY)
    uint8_t LYC = 0;             // 0xFF45 (current scanline compare (if LY == LYC, set flag in stat register))
    uint16_t scanlineCounter = 0;

    uint8_t SCY; // 0xFF42
    uint8_t SCX; // 0xFF43
    uint8_t WY;  // 0xFF4A
    uint8_t WX;  // 0xFF4B

    uint8_t BGP;  // 0xFF47 BG palette data
    uint8_t OBP0; // 0xFF48 Obj palette 0
    uint8_t OBP1; // 0xFF49 Obj palette 1

    Bus *bus = nullptr;
    Interrupts *interrupts = nullptr;
};