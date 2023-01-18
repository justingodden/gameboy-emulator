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

    uint16_t PC;
    // uint8_t currentRamBank = 0;
};