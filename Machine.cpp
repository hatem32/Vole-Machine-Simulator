#include "Machine.h"
#include <iostream>
#include <sstream>

using namespace std;

Machine::Machine() : executor(PC, IR, registers, memory) {}

void Machine::Banner()
{
    interface.Banner();
}

bool Machine::run()
{
    string instructionsStr = interface.rFile();
    string errorMsg = loadProgram(instructionsStr);

    if (!errorMsg.empty())
    {
        cout << "Error in loading the program!\n" << errorMsg << "\n\n";
        return interface.askAgain();
    }

    string screenOutput;
    executor.executeProgram(screenOutput);

    if (!screenOutput.empty() && screenOutput.back() != '\n')
        cout << '\n' << endl;

    if (interface.ask())
        interface.showOutput(screenOutput, PC, IR, registers, memory);

    return interface.askAgain();
}

string Machine::loadProgram(string &instructionsStr)
{
    int instructionsCount = 5;
    stringstream ss(instructionsStr);
    string instruction;

    while (ss >> instruction)
    {
        if (instructionsCount >= 128)
            return "The maximum number of instructions is 128.";

        if (instruction.length() != 4)
            return "Instruction \"" + instruction + "\" should be 4 characters long.";

        char opCode = tolower(instruction[0]);
        char reg1Addr, reg2Addr, reg3Addr;
        string memAddr;

        switch (opCode)
        {
        case '1':
        case '2':
        case '3':
        case 'b':
            reg1Addr = instruction[1];
            memAddr = instruction.substr(2);
            if (!isxdigit(reg1Addr) || !isxdigit(memAddr[0]) || !isxdigit(memAddr[1]))
                return "Invalid Register or Memory address in instruction \"" + instruction + "\"";
            break;
        case '4':
            if (instruction[1] != '0' || !isxdigit(instruction[2]) || !isxdigit(instruction[3]))
                return "Invalid Instruction \"" + instruction + "\"";
            break;
        case '5':
        case '6':
            reg1Addr = instruction[1];
            reg2Addr = instruction[2];
            reg3Addr = instruction[3];
            if (!isxdigit(reg1Addr) || !isxdigit(reg2Addr) || !isxdigit(reg3Addr))
                return "Invalid Register Address in instruction \"" + instruction + "\"";
            break;
        case 'c':
            if (instruction.substr(1) != "000")
                return "Invalid Instruction \"" + instruction + "\"";
            break;
        default:
            return "Undefined Op-Code \"" + string(1, opCode) + "\" in instruction \"" + instruction + "\"";
        }

        stringstream instructionSS(instruction);
        uint16_t encodedInstruction;
        instructionSS >> hex >> encodedInstruction;

        uint8_t leftSide = encodedInstruction >> 8;
        uint8_t rightSide = encodedInstruction & 0xFF;

        memory.setValue(instructionsCount * 2, leftSide);
        memory.setValue(instructionsCount * 2 + 1, rightSide);

        instructionsCount++;
    }

    return "";
}
