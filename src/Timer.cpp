#include "Timer.h"

Timer::Timer()
{
}

Timer::~Timer()
{
}

void Timer::setInterrupts(Interrupts *interrupts)
{
    interrupts = interrupts;
}

void Timer::update(unsigned int cycles)
{
    updateDividers(cycles);

    if (TAC & 0b00000100) // clock-enabled flag
    {
        timerCounter += cycles;

        if (timerCounter >= timerSpeed)
        {
            timerCounter = 0;
            setTimerSpeed();

            if (TIMA > 255)
            {
                TIMA = TMA;
                interrupts->requestInterrupt(2);
            }
            else
            {
                TIMA++;
            }
        }
    }
}

void Timer::updateDividers(unsigned int cycles)
{
    divCounter += cycles;

    if (divCounter > 255)
    {
        DIV++;
        divCounter = 0; // or is it -= 256?
    }
}

void Timer::setTimerSpeed()
{
    switch (TAC & 0b00000011)
    {
    case 0b00000000:
        timerSpeed = 1024;
        break;

    case 0b00000001:
        timerSpeed = 16;
        break;

    case 0b00000010:
        timerSpeed = 64;
        break;

    case 0b00000011:
        timerSpeed = 256;
        break;

    default:
        break;
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
        return 0;
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