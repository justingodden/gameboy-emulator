#include "Gameboy.h"

Gameboy::Gameboy(Cart *cart)
    : cart(cart)
{
    Display *display = new Display;
    Joypad *joypad = new Joypad;
    Memory *memory = new Memory;
    Ppu *ppu = new Ppu;
    Timer *timer = new Timer;

    Bus *bus = new Bus(cart, interrupts, joypad, memory, ppu, timer);
    Cpu *cpu = new Cpu;
    Interrupts *interrupts = new Interrupts;

    cpu->setBus(bus);
    interrupts->setCpu(cpu);
    ppu->setBus(bus);
    ppu->setInterrupts(interrupts);
    timer->setInterrupts(interrupts);
}

Gameboy::~Gameboy()
{
    delete display;
    delete joypad;
    delete memory;
    delete ppu;
    delete timer;
    delete bus;
    delete cpu;
    delete interrupts;
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

    display->update(ppu->getScreenData());
}