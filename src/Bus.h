#pragma once

#include <stdint.h>
#include "Cart.h"
#include "Cpu.h"
#include "Joypad.h"
#include "Ppu.h"

class Bus
{
public:
    Bus(Cart *cart, Cpu *cpu, Joypad *joypad, Ppu *ppu);
    ~Bus();

public:
    uint8_t readByte(uint16_t addr) const;
    void writeByte(uint16_t addr, uint8_t data);

private:
    Cart *cart = nullptr;
    Cpu *cpu = nullptr;
    Joypad *joypad = nullptr;
    Ppu *ppu = nullptr;
};
