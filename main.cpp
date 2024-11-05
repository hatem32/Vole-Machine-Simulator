#include "Machine.h"

int main()
{
    Machine *machine = new Machine();
    machine->Banner();
    while (machine->run())
    {
        machine = new Machine();
    }

    return 0;
}