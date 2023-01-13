#pragma once

#include <stdint.h>

class Joypad
{
public:
    Joypad();
    ~Joypad();

public:
    uint8_t readByte();
    void writeByte(uint8_t data);

private:
    uint8_t joypad;
};