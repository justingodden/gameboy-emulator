#pragma once

#include "stdint.h"
#include "Cpu.h"

class Cpu;

class Interrupts
{
public:
    Interrupts(Cpu *cpu);
    ~Interrupts();

public:
    void update();
    void requestInterrupt(uint8_t code);

private:
    void doInterrupt(unsigned int i);

private:
    bool IME;   // interrupt master enable flag - no bus address
    uint8_t IE; // interrupt enable - 0xFFFF
    uint8_t IF; // interrupt flag - 0xFF0F
    Cpu *cpu = nullptr;
};