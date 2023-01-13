#include "Gameboy.h"
#include "Joypad.h"
#include "Ppu.h"

Gameboy::Gameboy(Cart *cart)
    : cart(cart)
{
    Cpu *cpu = new Cpu;
    Ppu *ppu = new Ppu;
    Joypad *joypad = new Joypad;

    Bus *bus = new Bus(cart, cpu, joypad, ppu);
}

Gameboy::~Gameboy()
{
    delete cpu;
    delete ppu;
    delete joypad;
    delete bus;
}