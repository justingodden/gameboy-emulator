#pragma once

#include "Bus.h"
#include "Cart.h"
#include "Cpu.h"
#include "Display.h"
#include "Interrupts.h"
#include "Joypad.h"
#include "Ppu.h"
#include "Timer.h"

class Gameboy
{
public:
    Gameboy(Cart *cart);
    ~Gameboy();

public:
    void Update();

private:
    Bus *bus = nullptr;
    Cart *cart = nullptr;
    Cpu *cpu = nullptr;
    Display *display = nullptr;
    Interrupts *interrupts = nullptr;
    Joypad *joypad = nullptr;
    Ppu *ppu = nullptr;
    Timer *timer = nullptr;
};
