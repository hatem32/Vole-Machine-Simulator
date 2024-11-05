#ifndef MEMORY_H
#define MEMORY_H

#include <array>
#include <iostream>
#include <cinttypes>

using namespace std;

#define MEMORY_COUNT 256

class Memory
{
private:
    array<unsigned char, MEMORY_COUNT> memory; // 256 memory locations

public:
    Memory();

    // Get the value stored in a specific memory address
    unsigned char getValue(int address) const;

    // Set the value at a specific memory address
    void setValue(int address, unsigned char value);


};

#endif // MEMORY_H
