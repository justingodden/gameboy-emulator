#include "Cpu.h"

Cpu::Cpu()
{
    std::fill(wRam.begin(), wRam.end(), 0);
    std::fill(hRam.begin(), hRam.end(), 0);
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

uint8_t Cpu::readWRam(uint16_t addr)
{
    return wRam[addr];
}

void Cpu::writeWRam(uint16_t addr, uint8_t data)
{
    wRam[addr] = data;
}

uint8_t Cpu::readHRam(uint16_t addr)
{
    return hRam[addr];
}

void Cpu::writeHRam(uint16_t addr, uint8_t data)
{
    hRam[addr] = data;
}
