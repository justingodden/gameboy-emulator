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

std::array<uint8_t, 160 * 144 * 4> Ppu::getScreenData()
{
    return screenData;
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

    case 0xFF42:
        return SCY;

    case 0xFF43:
        return SCX;

    case 0xFF44:
        return currentScanline;

    case 0xFF45:
        return LYC;

    case 0xFF46:
        return 0; // dma  - read-only?

    case 0xFF47:
        return BGP;

    case 0xFF48:
        return OBP0;

    case 0xFF49:
        return OBP1;

    case 0xFF4A:
        return WY;

    case 0xFF4B:
        return WX;

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

    case 0xFF42:
        SCY = data;
        break;

    case 0xFF43:
        SCX = data;
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

    case 0xFF47:
        BGP = data;
        break;

    case 0xFF48:
        OBP0 = data;
        break;

    case 0xFF49:
        OBP1 = data;
        break;

    case 0xFF4A:
        WY = data;
        break;

    case 0xFF4B:
        WX = data;
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
    scanlineCounter += cycles;

    if (scanlineCounter >= 456) // 456 clock cycles per scanline draw
    {
        scanlineCounter = 0;
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
            drawScanline();
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
        scanlineCounter = 0;
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
        if (scanlineCounter <= 80)
        {
            lcdStatus &= 0b11111100; // zero last 2 bytes
            lcdStatus |= 2;          // set to mode 2
            interruptRequested = lcdStatus & 0b00100000;
        }

        // mode 3 (next 172 clock cycles)
        else if (scanlineCounter <= (80 + 172))
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

void Ppu::drawScanline()
{
    if (lcdControl & 0b00000001)
    {
        renderTiles();
    }

    if (lcdControl & 0b00000010)
    {
        renderSprites();
    }
}

void Ppu::renderTiles()
{
    uint8_t wXActual = WX - 7;
    bool signed_ = false;

    // check window enabled
    bool windowEnabled = false;
    if (lcdControl & 0b00100000)
    {
        if (WY <= currentScanline)
        {
            windowEnabled = true;
        }
    }

    // 0x8000 vram addressing mode
    uint16_t basePointer = 0;
    // which tile data: 0=8800-97FF, 1=8000-8FFF
    if (!(lcdControl & 0b00010000))
    {
        // 0x8800 vram addressing mode
        basePointer += 0x1000;
        signed_ = true;
    }

    // set tilemap area
    uint16_t tilemapArea;
    if (windowEnabled)
    {
        if (lcdControl & 0b01000000)
        {
            tilemapArea = 0x1C00; // 0x9C00 on bus
        }
        else
        {
            tilemapArea = 0x1800; // 0x9800 on bus
        }
    }
    else
    {
        if (lcdControl & 0b00001000)
        {
            tilemapArea = 0x1C00; // 0x9C00 on bus
        }
        else
        {
            tilemapArea = 0x1800; // 0x9800 on bus
        }
    }

    // ACTUAL scanline - i.e. not just within viewport
    uint8_t yPos;
    if (!windowEnabled)
    {
        yPos = SCY + currentScanline;
    }
    else
    {
        yPos = currentScanline - WY; // TODO: double check this
    }

    // vertical tile number
    uint8_t vTileNum = yPos / 8;

    // draw 160 horizontal pixels
    for (uint8_t pixel = 0; pixel < 160; pixel++)
    {
        uint8_t xPos = SCX + pixel;

        if (windowEnabled)
        {
            if (pixel >= wXActual)
            {
                xPos = pixel - wXActual;
            }
        }

        // horizontal tile number
        uint8_t hTileNum = xPos / 8;

        uint16_t addr = tilemapArea + (vTileNum * 32) + hTileNum;

        uint8_t tileNum; // needs initial declaration
        if (signed_)
        {
            int8_t tileNum = static_cast<int8_t>(vRam[addr]);
        }
        else
        {
            uint8_t tileNum = vRam[addr];
        }

        uint16_t tileLocation = basePointer + tileNum * 16; // TODO: check this!

        // current vertical pixel of the current tile
        uint8_t tileRow = yPos % 8;
        tileRow *= 2; // each line takes up two bytes of memory
        // TODO: check these!
        uint8_t colourByte1 = vRam[tileLocation + (tileRow)-0x8000];
        uint8_t colourByte2 = vRam[tileLocation + (tileRow)-0x8000 + 1];

        int8_t tileCol = xPos % 8;
        tileCol -= 7;
        tileCol *= -1;

        uint8_t colourNum = (colourByte2 & (1 << tileCol));
        colourNum <<= 1;
        colourNum |= (colourByte1 & (1 << tileCol));

        COLOUR colour = getColour(colourNum, BGP);

        // setup the RGB values
        int red, green, blue;
        switch (colour)
        {
        case WHITE:
            red = 255;
            green = 255;
            blue = 255;
            break;
        case LIGHT_GRAY:
            red = 0xCC;
            green = 0xCC;
            blue = 0xCC;
            break;
        case DARK_GRAY:
            red = 0x77;
            green = 0x77;
            blue = 0x77;
            break;
        case BLACK:
            red = 0;
            green = 0;
            blue = 0;
            break;
        }

        if (currentScanline > 143 || pixel > 159)
        {
            continue;
        }

        screenData[pixel + (currentScanline * 160)] = red;
        screenData[pixel + (currentScanline * 160) + 1] = green;
        screenData[pixel + (currentScanline * 160) + 2] = blue;
        screenData[pixel + (currentScanline * 160) + 3] = 255; // alpha
    }
}

void Ppu::renderSprites()
{
}

COLOUR Ppu::getColour(uint8_t num, uint16_t addr)
{
    uint8_t hi, lo;

    // which bits of the colour palette does the colour id map to?
    switch (num)
    {
    case 0:
        hi = 1;
        lo = 0;
        break;
    case 1:
        hi = 3;
        lo = 2;
        break;
    case 2:
        hi = 5;
        lo = 4;
        break;
    case 3:
        hi = 7;
        lo = 6;
        break;
    }

    int colour = BGP & (1 << hi) << 1;
    colour |= BGP & (1 << lo);

    // convert the game colour to emulator colour
    switch (colour)
    {
    case 0:
        return WHITE;
    case 1:
        return LIGHT_GRAY;
    case 2:
        return DARK_GRAY;
    case 3:
        return BLACK;
    default:
        return WHITE;
    }
}
