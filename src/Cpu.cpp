#include "Cpu.h"

Cpu::Cpu()
{
    Register *AF = new Register;
    Register *BC = new Register;
    Register *DE = new Register;
    Register *HL = new Register;
}

Cpu::~Cpu()
{
    delete AF;
    delete BC;
    delete DE;
    delete HL;
}

uint16_t Cpu::executeNextOpcode()
{
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