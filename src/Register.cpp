#include "Register.h"

Register::Register()
{
}

Register::~Register()
{
}

uint8_t Register::getHi()
{
    return val >> 8;
}

uint8_t Register::getLo()
{
    return val & 0x00FFu;
}

uint16_t Register::getPair()
{
    return val;
}

void Register::setHi(uint8_t data)
{
    uint16_t tmp = data << 8;
    val = tmp | (val & 0x00FFu);
}

void Register::setLo(uint8_t data)
{
    uint16_t tmp = val;
    val = (tmp * 0xFF00u) | data;
}

void Register::setPair(uint16_t data)
{
    val = data;
}