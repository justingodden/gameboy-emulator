#include "Bus.h"

Bus::Bus(Cart *cart, Interrupts *interrupts, Joypad *joypad, Memory *memory, Ppu *ppu, Timer *timer)
    : cart(cart), interrupts(interrupts), joypad(joypad), memory(memory), ppu(ppu), timer(timer)
{
}

Bus::~Bus()
{
}

uint8_t Bus::readByte(uint16_t addr) const
{
    // 16k rom bank 00
    if (addr < 0x4000)
    {
        return cart->readRomByte(addr);
    }

    // 16k rom bank 01~NN
    else if (addr < 0x8000)
    {
        return cart->readRomByte((addr - 0x4000) + cart->currentRomBank * 0x4000);
    }

    // 8k VRAM
    else if (addr < 0xA000)
    {
        return ppu->readByte(addr - 0x8000);
    }

    // external cart sRam
    else if (addr < 0xC000)
    {
        return cart->readSRamByte(addr - 0xA000);
    }

    // work ram
    else if (addr < 0xE000)
    {
        return memory->readWRam(addr - 0xC000);
    }

    // ECHO ram
    else if (addr < 0xFE00)
    {
        return memory->readWRam(addr - 0xE000);
    }

    // sprite attribute table (OAM)
    else if (addr < 0xFEA0)
    {
        return 0x00; // TODO
    }

    // not usable
    else if (addr < 0xFF00)
    {
        return 0x00;
    }

    // I/O registers
    // joypad
    else if (addr == 0xFF00)
    {
        return joypad->readByte();
    }

    // serial transfer 0xFF01 - 0xFF02

    // timer and divider 0xFF04 - 0xFF07
    else if ((0xFF04 <= addr) && (addr <= 0xFF07))
    {
        return timer->readByte(addr);
    }

    // audio 0xFF10 - 0xFF26

    // wave pattern 0xFF30 - 0xFF3F

    // LCD control, status, position, scrolling, palettes 0xFF40 - 0x4B

    // vram bank select 0xFF4F

    // disable boot room 0xFF50

    // vram dma 0xFF68 - 0xFF69

    // bg / obj palletes 0xFF68 - 0xFF69

    // wram bank select 0xFF70

    // hram
    else if ((0xFF80 <= addr) && (addr <= 0xFFFE))
    {
        return memory->readHRam(addr);
    }

    // interrupt enable register
    else if (addr == 0xFFFF)
    {
        return 0x00; // TODO
    }

    return 0x00;
}

void Bus::writeByte(uint16_t addr, uint8_t data)
{
    // Not allowed - read-only memory
    if (addr < 0x8000)
    {
    }

    // 8k VRAM
    else if (addr < 0xA000)
    {
        ppu->writeByte(addr + 0x8000, data);
    }

    // external cart sRam
    else if (addr < 0xC000)
    {
        cart->writeSRamByte(addr - 0xA000, data);
    }

    // external cart sRam
    else if (addr < 0xC000)
    {
        return cart->writeSRamByte(addr - 0xA000, data);
    }

    // work ram
    else if (addr < 0xE000)
    {
        return memory->writeWRam(addr - 0xC000, data);
    }

    // ECHO ram
    else if (addr < 0xFE00)
    {
        return memory->writeWRam(addr - 0xE000, data);
    }

    // sprite attribute table (OAM)
    else if (addr < 0xFEA0)
    {
    }

    // not usable
    else if (addr < 0xFF00)
    {
    }

    // I/O registers
    // joypad
    else if (addr == 0xFF00)
    {
        return joypad->writeByte(data);
    }

    // serial transfer 0xFF01 - 0xFF02

    // timer and divider 0xFF04 - 0xFF07
    else if ((0xFF04 <= addr) && (addr <= 0xFF07))
    {
        return timer->writeByte(addr, data);
    }

    // audio 0xFF10 - 0xFF26

    // wave pattern 0xFF30 - 0xFF3F

    // LCD control, status, position, scrolling, palettes 0xFF40 - 0x4B

    // vram bank select 0xFF4F

    // disable boot room 0xFF50

    // vram dma 0xFF68 - 0xFF69

    // bg / obj palletes 0xFF68 - 0xFF69

    // wram bank select 0xFF70

    // hram
    else if ((0xFF80 <= addr) && (addr <= 0xFFFE))
    {
        memory->writeHRam(addr, data);
    }

    // interrupt enable register
    else if (addr == 0xFFFF)
    {
    }
}