#pragma once

#include "Cpu.h"
#include "Cart.h"
#include "Bus.h"

class Gameboy
{
public:
    Gameboy(Cart *cart);
    ~Gameboy();

private:
    Cpu *cpu = nullptr;
    Cart *cart = nullptr;
    Bus *bus = nullptr;
    Ppu *ppu = nullptr;
};
