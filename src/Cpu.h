#pragma once

#include "Cart.h"
#include "Register.h"

class Cpu
{
public:
    Cpu();
    ~Cpu();

private:
    Cart *cart = nullptr;

    Register *AF = nullptr;
    Register *BC = nullptr;
    Register *DE = nullptr;
    Register *HL = nullptr;
};