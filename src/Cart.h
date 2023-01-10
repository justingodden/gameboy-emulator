#pragma once

#include <array>
#include <string>
#include <stdint.h>

class Cart
{
public:
    Cart(std::string romPath);
    ~Cart();

private:
    void loadRom();

public:
    std::array<uint8_t, 0x200000> romData;

private:
    std::string romPath;
};