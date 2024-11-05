#include <iostream>
#include <iomanip>
#include "memory.h"

using namespace std;

// Constructor initializing memory to zero
Memory::Memory() : memory{} {}

// Get the value stored in a specific memory address
unsigned char Memory::getValue(int address) const
{
    if (address < 0 || address >= MEMORY_COUNT)
    {
        throw out_of_range("Memory address out of range");
    }
    return memory[address];
}

// Set the value at a specific memory address
void Memory::setValue(int address, unsigned char value)
{
    if (address < 0 || address >= MEMORY_COUNT)
    {
        throw out_of_range("Memory address out of range");
    }
    memory[address] = value;
}
