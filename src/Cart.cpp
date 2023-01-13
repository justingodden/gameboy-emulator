#include <iostream>
#include <fstream>
#include <vector>

#include "Cart.h"

Cart::Cart(std::string romPath)
    : romPath(romPath)
{
    std::fill(romData.begin(), romData.end(), 0);
    loadRom();
    if (!headerChecksum())
    {
        throw;
    }
    setRomBankMode();
    printCartHeader();
}

Cart::~Cart()
{
}

void Cart::loadRom()
{
    std::ifstream input(romPath, std::ios::binary);
    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});

    for (long i = 0; i < buffer.size(); i++)
    {
        romData[i] = buffer[i];
    }
}

void Cart::setRomBankMode()
{
    switch (romData[0x174])
    {
    case 1:
        MBC1 = true;
        break;
    case 2:
        MBC1 = true;
        break;
    case 3:
        MBC1 = true;
        break;
    case 5:
        MBC2 = true;
        break;
    case 6:
        MBC2 = true;
        break;
    default:
        break;
    }
}

bool Cart::headerChecksum()
{
    uint8_t checksum = 0;
    for (uint16_t address = 0x0134; address <= 0x014C; address++)
    {
        checksum = checksum - romData[address] - 1;
    }

    return (checksum & 0xFF) == romData[0x14D];
}

void Cart::printCartHeader()
{
    std::cout << "Title: ";
    for (uint16_t i = 0x0134; i <= 0x0143; i++)
    {
        std::cout << romData[i];
    }
    std::cout << "\n";

    std::cout << "Licencee Code: ";
    if (romData[0x014B] == 0x33)
    {
        const char char1 = romData[0x0144];
        const char char2 = romData[0x0145];
        std::string code = "";
        code += char1;
        code += char2;
        std::cout << newLicenceeCode[code] << std::endl;
    }
    else
    {
        std::cout << oldLicenceeCode[romData[0x014B]] << std::endl;
    }
}