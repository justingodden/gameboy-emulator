#pragma once

#include <stack>
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

    uint16_t executeNextOpcode();

    void setPc(uint16_t addr);
    uint16_t getPc();

public:
    std::stack<uint16_t> stack;

private:
    Cart *cart = nullptr;

    Register *AF = nullptr;
    Register *BC = nullptr;
    Register *DE = nullptr;
    Register *HL = nullptr;

    std::array<uint8_t, 0x2000> wRam;            // work ram
    std::array<uint8_t, (0xFFFF - 0xFF80)> hRam; // high ram

    uint16_t PC;
    // uint8_t currentRamBank = 0;
};