#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "Registers.h"
#include "Memory.h"
#include <cinttypes>
#include <string>

using namespace std;

class Executor
{
private:
    uint8_t &PC;
    uint16_t &IR;
    Registers &registers;
    Memory &memory;
    string *screenOutput;

    uint8_t getSecondByte();
    uint8_t getFirst4Bits();
    uint8_t getSecond4Bits();
    uint8_t getThird4Bits();
    uint8_t getFourth4Bits();

    uint8_t getSign(uint8_t byte);
    uint8_t getExponent(uint8_t byte);
    uint8_t getMantissa(uint8_t byte);

    bool executeInstruction();

public:
    Executor(uint8_t &_PC, uint16_t &_IR, Registers &_registers, Memory &_memory);
    void executeProgram(string &_screenOutput);
};

#endif // EXECUTOR_H
