#ifndef INTERFACE_H
#define INTERFACE_H

#include <iostream>
#include <string>
#include "Registers.h"
#include "Memory.h"
#include <cinttypes>

class Interface
{
public:
    void Banner();
    std::string rFile();
    bool ask();
    void showOutput(std::string &screenOutput, uint8_t &PC, uint16_t &IR, Registers &registers, Memory &memory);
    bool askAgain();
};

#endif // INTERFACE_H
