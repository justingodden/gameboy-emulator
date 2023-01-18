#include "Interrupts.h"

Interrupts::Interrupts(Cpu *cpu)
    : cpu(cpu)
{
}

Interrupts::~Interrupts()
{
}

void Interrupts::update()
{
    if (IME)
    {
        if (IF > 0)
        {
            for (unsigned int i = 0; i < 5; i++)
            {
                if (IE & (1 << i))
                {
                    if (IF & (1 << i))
                    {
                        doInterrupt(i);
                    }
                }
            }
        }
    }
}

void Interrupts::doInterrupt(unsigned int i)
{
    IME = false;
    IF &= ~(1 << i); // reset bit

    cpu->pushToStack(cpu->getPc());

    switch (i)
    {
    case 0:
        cpu->setPc(0x40);
        break;
    case 1:
        cpu->setPc(0x48);
        break;
    case 2:
        cpu->setPc(0x50);
        break;
    case 4:
        cpu->setPc(0x60);
        break;
    default:
        break;
    }
}

void Interrupts::requestInterrupt(uint8_t code)
{
    switch (code)
    {
    case 0:
        IF |= (1 << code);
        break;
    case 1:
        IF |= (1 << code);
        break;
    case 2:
        IF |= (1 << code);
        break;
    case 4:
        IF |= (1 << code);
        break;
    default:
        break;
    }
}