#pragma once

#include <stdint.h>

class Register
{
public:
    Register();
    ~Register();

public:
    uint8_t getHi();
    uint8_t getLo();
    uint16_t getPair();

    void setHi(uint8_t data);
    void setLo(uint8_t data);
    void setPair(uint16_t data);

private:
    uint16_t val;
};