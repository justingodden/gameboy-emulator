#pragma once

#include "Bus.h"
#include "Register.h"

class Bus;

class Cpu
{
public:
    Cpu(Bus *bus);
    ~Cpu();

public:
    uint16_t executeNextOpcode();

    void setPc(uint16_t addr);
    uint16_t getPc();

    void pushToStack(uint8_t data);
    uint8_t popFromStack();

private:
    uint16_t getAF();
    uint16_t getBC();
    uint16_t getDE();
    uint16_t getHL();

    bool getFlagZ();
    bool getFlagN();
    bool getFlagH();
    bool getFlagC();

private:
    uint8_t regA;
    uint8_t regF;
    uint8_t regB;
    uint8_t regC;
    uint8_t regD;
    uint8_t regE;
    uint8_t regH;
    uint8_t regL;

    uint16_t PC = 0x0100;
    uint16_t SP = 0xFFFE;
    Bus *bus = nullptr;
    // uint8_t currentRamBank = 0;
};