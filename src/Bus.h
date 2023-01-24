#pragma once

#include <stdint.h>
#include "Cart.h"
#include "Interrupts.h"
#include "Joypad.h"
#include "Memory.h"
#include "Ppu.h"
#include "Timer.h"

class Interrupts;
class Ppu;
class Timer;

class Bus
{
public:
    Bus(Cart *cart, Interrupts *interrupts, Joypad *joypad, Memory *memory, Ppu *ppu, Timer *timer);
    ~Bus();

public:
    uint8_t readByte(uint16_t addr) const;
    void writeByte(uint16_t addr, uint8_t data);

private:
    Cart *cart = nullptr;
    Interrupts *interrupts = nullptr;
    Joypad *joypad = nullptr;
    Memory *memory = nullptr;
    Ppu *ppu = nullptr;
    Timer *timer = nullptr;
};
