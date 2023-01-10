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