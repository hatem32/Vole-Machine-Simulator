#include <cmath>
#include "Executor.h"

Executor::Executor(uint8_t &_PC, uint16_t &_IR, Registers &_registers, Memory &_memory) 
    : PC(_PC), IR(_IR), registers(_registers), memory(_memory) { }

uint8_t Executor::getSecondByte() { return IR; }
uint8_t Executor::getFirst4Bits() { return IR >> 12; }
uint8_t Executor::getSecond4Bits() { return (uint16_t)(IR << 4) >> 12; }
uint8_t Executor::getThird4Bits() { return (uint16_t)(IR << 8) >> 12; }
uint8_t Executor::getFourth4Bits() { return (uint16_t)(IR << 12) >> 12; }

bool Executor::executeInstruction() {
    uint8_t data, data2, result;
    IR = (memory.getValue(PC) << 8) + memory.getValue(PC + 1);

    switch (getFirst4Bits()) {
    case 1:  // Load from memory
        data = memory.getValue(getSecondByte());
        registers.setValue(getSecond4Bits(), data);
        break;
    case 2:  // Load immediate
        registers.setValue(getSecond4Bits(), getSecondByte());
        break;
    case 3:  // Store or output
        data = registers.getValue(getSecond4Bits());
        if (getSecondByte() == 0) {
            *screenOutput += data;
            cout << data;
        } else {
            memory.setValue(getSecondByte(), data);
        }
        break;
    case 4:  // Move register
        if (getSecond4Bits() != 0) {
            cerr << "Execution error, undefined instruction \"0x" << IR << "\".\n";
            return false;
        }
        data = registers.getValue(getThird4Bits());
        registers.setValue(getFourth4Bits(), data);
        break;
    case 5:  // Integer addition
        data = registers.getValue(getThird4Bits()) + registers.getValue(getFourth4Bits());
        registers.setValue(getSecond4Bits(), data);
        break;
    case 0xb:  // Jump if equal
        if (registers.getValue(0) == registers.getValue(getSecond4Bits())) {
            PC = getSecondByte();
            return true;
        }
        break;
    case 0xc:  // Halt
        if (getSecond4Bits() != 0 || getSecondByte() != 0) {
            cerr << "Execution error, undefined instruction \"0x" << IR << "\".\n";
        }
        return false;
    default:
        cerr << "Execution error, undefined instruction \"0x" << IR << "\".\n";
        return false;
    }

    if (PC == 254) {
        return false;  // Stop execution
    }

    PC += 2;
    return true;
}

void Executor::executeProgram(string &_screenOutput) {
    screenOutput = &_screenOutput;
    cerr << hex;
    while (executeInstruction()) { }
    cerr << dec;
}

