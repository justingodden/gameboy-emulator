#pragma once

#include <stdint.h>

class Timer
{
public:
    Timer();
    ~Timer();

public:
    void update(unsigned int cycles);
    uint8_t readByte(uint16_t addr);
    void writeByte(uint16_t addr, uint8_t data);

private:
    void updateDividers(unsigned int cycles);

private:
    uint8_t DIV;  // 0xFF04
    uint8_t TIMA; // 0xFF05
    uint8_t TMA;  // 0xFF06
    uint8_t TAC;  // 0xFF07
    uint32_t CLOCKSPEED = 4194304;
    uint16_t timerCounter = 1024;
    uint16_t divCounter = 0;
    bool clockEnabled;
};