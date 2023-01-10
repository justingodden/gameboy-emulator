#pragma once

#include <stdint.h>

class Bus
{
public:
    Bus();
    ~Bus();

public:
    uint8_t readByte(uint16_t addr);
    void writeByte(uint16_t addr, uint8_t data);
};
