#ifndef _MACHINE_H
#define _MACHINE_H

#include <iostream>
#include "Memory.h"
#include "Registers.h"
#include "Interface.h"
#include "Executor.h"
#include <cinttypes>

using namespace std;

class Machine
{
private:
    uint8_t PC = 0x0A;
    uint16_t IR;
    Registers registers;
    Memory memory;
    Executor executor;
    Interface interface;

    string loadProgram(string &instructionsStr);

public:
    Machine();
    void Banner();
    bool run();
};

#endif // _MACHINE_H
