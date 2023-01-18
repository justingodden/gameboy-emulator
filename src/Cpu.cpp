#include "Cpu.h"

Cpu::Cpu(Bus *bus)
    : bus(bus)
{
}

Cpu::~Cpu()
{
}

uint16_t Cpu::executeNextOpcode()
{
    uint8_t opcode = bus->readByte(PC);
    return 1;
}

void Cpu::setPc(uint16_t addr)
{
    PC = addr;
}

uint16_t Cpu::getPc()
{
    return PC;
}

void Cpu::pushToStack(uint8_t data)
{
    bus->writeByte(--SP, data);
}

uint8_t Cpu::popFromStack()
{
    return bus->readByte(SP++);
}

uint16_t Cpu::getAF()
{
    return (regA << 8) | regF;
}

uint16_t Cpu::getBC()
{
    return (regB << 8) | regC;
}

uint16_t Cpu::getDE()
{
    return (regD << 8) | regE;
}

uint16_t Cpu::getHL()
{
    return (regH << 8) | regL;
}

bool Cpu::getFlagZ()
{
    return (regF & (1 << 7) > 0);
}

bool Cpu::getFlagN()
{
    return (regF & (1 << 6) > 0);
}

bool Cpu::getFlagH()
{
    return (regF & (1 << 5) > 0);
}

bool Cpu::getFlagC()
{
    return (regF & (1 << 4) > 0);
}
