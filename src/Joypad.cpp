#include "Joypad.h"

Joypad::Joypad()
{
}

Joypad::~Joypad()
{
}

uint8_t Joypad::readByte()
{
    return joypad;
}

void Joypad::writeByte(uint8_t data)
{
    joypad = data;
}