#include "Gameboy.h"

Gameboy::Gameboy(Cart *cart)
    : cart(cart)
{
    Cpu *cpu = new Cpu;
    Display *display = new Display;
    Interrupts *interrupts = new Interrupts(cpu);
    Joypad *joypad = new Joypad;
    Ppu *ppu = new Ppu;
    Timer *timer = new Timer;

    Bus *bus = new Bus(cart, cpu, interrupts, joypad, ppu, timer);
}

Gameboy::~Gameboy()
{
    delete cpu;
    delete display;
    delete interrupts;
    delete joypad;
    delete ppu;
    delete timer;
    delete bus;
}

void Gameboy::Update()
{
    const int MAXCYCLES = 69905; // (4194304Hz / 60fps)
    uint16_t cyclesThisUpdate = 0;

    while (cyclesThisUpdate < MAXCYCLES)
    {
        unsigned int cycles = cpu->executeNextOpcode();
        cyclesThisUpdate += cycles;
        timer->update(cycles);
        ppu->update(cycles);
        interrupts->update();
    }

    display->update();
}