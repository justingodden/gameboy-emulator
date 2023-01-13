#pragma once

#include "Cart.h"
#include "Register.h"

class Cpu
{
public:
    Cpu();
    ~Cpu();

public:
    uint8_t readWRam(uint16_t addr);
    void writeWRam(uint16_t addr, uint8_t data);

    uint8_t readHRam(uint16_t addr);
    void writeHRam(uint16_t addr, uint8_t data);

public:
private:
    Cart *cart = nullptr;

    Register *AF = nullptr;
    Register *BC = nullptr;
    Register *DE = nullptr;
    Register *HL = nullptr;

    std::array<uint8_t, 0x2000> wRam;            // work ram
    std::array<uint8_t, (0xFFFF - 0xFF80)> hRam; // high ram
    // uint8_t currentRamBank = 0;
};