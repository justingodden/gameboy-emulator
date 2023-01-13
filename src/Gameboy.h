#pragma once

#include "Bus.h"
#include "Cart.h"
#include "Cpu.h"
#include "Joypad.h"
#include "Ppu.h"

class Gameboy
{
public:
    Gameboy(Cart *cart);
    ~Gameboy();

private:
    Bus *bus = nullptr;
    Cart *cart = nullptr;
    Cpu *cpu = nullptr;
    Joypad *joypad = nullptr;
    Ppu *ppu = nullptr;
};
