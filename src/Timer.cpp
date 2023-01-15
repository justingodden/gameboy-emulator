#include "Timer.h"

Timer::Timer()
{
}

Timer::~Timer()
{
}

void Timer::update(unsigned int cycles)
{
    updateDividers(cycles);

    if (TAC & 0b00000100)
    {
    }
}

void Timer::updateDividers(unsigned int cycles)
{
    divCounter += cycles;

    if (divCounter > 255)
    {
        DIV += cycles;
        divCounter = 0; // or is it -= 256?
    }
}

uint8_t Timer::readByte(uint16_t addr)
{
    switch (addr)
    {
    case 0xFF04:
        return DIV;

    case 0xFF05:
        return TIMA;

    case 0xFF06:
        return TMA;

    case 0xFF07:
        return TAC;

    default:
        break;
    }
}

void Timer::writeByte(uint16_t addr, uint8_t data)
{
    switch (addr)
    {
    case 0xFF04: // reset divider
        DIV = 0;
        divCounter = 0;
        break;

    case 0xFF05:
        TIMA = data;
        break;

    case 0xFF06:
        TMA = data;
        break;

    case 0xFF07:
        TAC = data;
        break;

    default:
        break;
    }
}