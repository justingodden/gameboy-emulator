#pragma once

#include "Cart.h"
#include "Display.h"
#include "Joypad.h"
#include "Memory.h"
#include "Ppu.h"
#include "Timer.h"
#include "Bus.h"
#include "Cpu.h"
#include "Interrupts.h"

class Gameboy
{
public:
    Gameboy(Cart *cart);
    ~Gameboy();

public:
    void Update();

private:
    Cart *cart = nullptr;
    Display *display = nullptr;
    Joypad *joypad = nullptr;
    Memory *memory = nullptr;
    Ppu *ppu = nullptr;
    Timer *timer = nullptr;
    Bus *bus = nullptr;
    Cpu *cpu = nullptr;
    Interrupts *interrupts = nullptr;
};
