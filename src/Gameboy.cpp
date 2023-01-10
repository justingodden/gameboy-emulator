#include "Gameboy.h"
#include "Ppu.h"

Gameboy::Gameboy(Cart *cart)
    : cart(cart)
{
    Cpu *cpu = new Cpu;
    Bus *bus = new Bus;
    Ppu *ppu = new Ppu;
}

Gameboy::~Gameboy()
{
    delete cpu;
    delete bus;
    delete ppu;
}