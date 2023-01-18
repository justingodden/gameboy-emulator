#pragma once

#include <stdint.h>
#include "Cart.h"
#include "Cpu.h"
#include "Interrupts.h"
#include "Joypad.h"
#include "Memory.h"
#include "Ppu.h"
#include "Timer.h"

class Bus
{
public:
    Bus(Cart *cart, Cpu *cpu, Interrupts *interrupts, Joypad *joypad, Memory *memory, Ppu *ppu, Timer *timer);
    ~Bus();

public:
    uint8_t readByte(uint16_t addr) const;
    void writeByte(uint16_t addr, uint8_t data);

private:
    Cart *cart = nullptr;
    Cpu *cpu = nullptr;
    Interrupts *interrupts = nullptr;
    Joypad *joypad = nullptr;
    Memory *memory = nullptr;
    Ppu *ppu = nullptr;
    Timer *timer = nullptr;
};
