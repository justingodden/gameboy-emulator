#include <fstream>
#include <vector>
#include "Cart.h"

Cart::Cart(std::string romPath)
    : romPath(romPath)
{
    std::fill(romData.begin(), romData.end(), 0);
    loadRom();
}

Cart::~Cart()
{
}

void Cart::loadRom()
{
    std::ifstream input(romPath, std::ios::binary);
    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});

    for (long i = 0; i < buffer.size(); ++i)
    {
        romData[i] = buffer[i];
    }
}