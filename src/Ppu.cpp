#include "Ppu.h"

Ppu::Ppu()
{
    std::fill(vRam.begin(), vRam.end(), 0);
}

Ppu::~Ppu()
{
}

void Ppu::setBus(Bus *bus)
{
    bus = bus;
}

void Ppu::setInterrupts(Interrupts *interrupts)
{
    interrupts = interrupts;
}

uint8_t Ppu::readVRamByte(uint16_t addr) const
{
    return vRam[addr];
}

void Ppu::writeVRamByte(uint16_t addr, uint8_t data)
{
    vRam[addr] = data;
}

uint8_t Ppu::readLcdByte(uint16_t addr) const
{
    switch (addr)
    {
    case 0xFF40:
        return lcdControl;
    case 0xFF41:
        return lcdStatus;
    case 0xFF44:
        return currentScanline;
    case 0xFF45:
        return LYC;
    default:
        return 0;
    }
}

void Ppu::writeLcdByte(uint16_t addr, uint8_t data)
{
    switch (addr)
    {
    case 0xFF40:
        lcdControl = data;
        break;
    case 0xFF41:
        lcdStatus = data;
        break;
    case 0xFF44:
        currentScanline = 0; // not sure if this is correct. pandocs says read-only
        break;
    case 0xFF45:
        LYC = data;
        break;
    case 0xFF46:
        dmaTranser(data);
        break;
    default:
        break;
    }
}

void Ppu::update(unsigned int cycles)
{
    setLcdStatus();

    if (!lcdEnabled())
    {
        return;
    }
    scalineCounter += cycles;

    if (scalineCounter >= 456) // 456 clock cycles per scanline draw
    {
        scalineCounter = 0;
        currentScanline++;

        if (currentScanline == 144)
        {
            interrupts->requestInterrupt(0);
            return;
        }

        if (currentScanline > 153)
        {
            currentScanline = 0;
            return;
        }

        if (currentScanline < 144)
        {
            // drawScanline(); // TODO
            return;
        }
    }
}

void Ppu::dmaTranser(uint8_t data)
{
    uint16_t addr = data << 8;
    for (unsigned int i = 0; i < 0xA0; i++)
    {
        bus->writeByte(0xFE00 + i, bus->readByte(addr + i));
    }
}

bool Ppu::lcdEnabled()
{
    return (lcdControl & (1 << 7)) > 0; // LCD enabled bit
}

void Ppu::setLcdStatus()
{
    // set lcd status to mode 1 V-Blank
    // during lcd disabled and scanline reset
    if (!lcdEnabled())
    {
        currentScanline = 0;
        scalineCounter = 0;
        lcdStatus &= 0b11111100; // zero last 2 bytes
        lcdStatus |= 1;          // set to mode 1
        return;
    }
    uint8_t currentMode = lcdStatus & 3;
    uint8_t interruptRequested = 0;

    if (currentScanline >= 144)
    {
        lcdStatus &= 0b11111100; // zero last 2 bytes
        lcdStatus |= 1;          // set to mode 1
        interruptRequested = lcdStatus & 0b00010000;
    }
    else
    {
        // mode 2 (first 80 clock cycles)
        if (scalineCounter <= 80)
        {
            lcdStatus &= 0b11111100; // zero last 2 bytes
            lcdStatus |= 2;          // set to mode 2
            interruptRequested = lcdStatus & 0b00100000;
        }

        // mode 3 (next 172 clock cycles)
        else if (scalineCounter <= (80 + 172))
        {
            lcdStatus &= 0b11111100; // zero last 2 bytes
            lcdStatus |= 3;          // set to mode 1
        }

        // mode 0
        else
        {
            lcdStatus &= 0b11111100; // zero last 2 bytes
            interruptRequested = lcdStatus & 0b00001000;
        }

        // entering new mode, so request interrupt
        if (currentMode != (lcdStatus & 3) && interruptRequested)
        {
            interrupts->requestInterrupt(1);
        }

        if (currentScanline == LYC)
        {
            lcdStatus |= 0b00000100; // set 2nd status bit to 1
            if (lcdStatus | 0b01000000)
            {
                interrupts->requestInterrupt(1);
            }
        }
        else
        {
            lcdStatus &= 0b11111011;
        }
    }
}
