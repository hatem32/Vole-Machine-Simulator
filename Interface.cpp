#include <iostream>
#include <fstream>
#include <iomanip>
#include "Interface.h"
#include "Memory.h"
#include "Registers.h"

using namespace std;

void Interface::Banner() {
    cout << "Hello!\n" << endl;
    cout << "This is a simulation of Vole machine.\n" << endl;
}

string Interface::rFile() {
    ifstream file;
    string fileContent, fileName;

    while (true) {
        cout << "Enter the name of the instructions file (.txt): ";
        getline(cin, fileName);
        file.open(fileName);

        if (!file) {
            cout << "This file can't be opened, please try again!\n";
            continue;
        }

        fileContent.assign((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        file.close();
        cout << endl;
        return fileContent;
    }
}

bool Interface::ask() {
    cout << "Do you want to see screen output and machine status? (y/n): ";

    while (true) {
        string choice;
        getline(cin, choice);

        if (choice == "y" || choice == "Y") {
            cout << endl;
            return true;
        } else if (choice == "n" || choice == "N") {
            cout << endl;
            return false;
        } else {
            cout << "Invalid input, please enter 'y' or 'n': ";
        }
    }
}

void Interface::showOutput(string &screenOutput, uint8_t &PC, uint16_t &IR, Registers &registers, Memory &memory) {
    cout << setfill('=') << setw(32) << " SCREEN OUTPUT " << setw(32) << '=' << '\n';
    cout << screenOutput << (screenOutput.back() != '\n' ? "\n" : "");
    cout << setw(64) << '=' << "\n\n";

    cout << setw(32) << " REGISTERS STATE " << setw(32) << '=' << '\n';
    cout << setfill(' ') << "PC : 0x" << hex << (int)PC << "\nIR : 0x" << IR << "\n" << left;

    for (int i = 0; i < REGISTERS_COUNT; i++) {
        cout << "R" << dec << setw(2) << i << ": 0x" << hex << (int)registers.getValue(i) << ((i != REGISTERS_COUNT - 1) ? "\n" : "");
    }
    cout << '\n' << right << setfill('=') << setw(64) << '=' << "\n\n";

    cout << setw(32) << " MEMORY STATE " << setw(32) << '=' << '\n' << setfill(' ') << left;
    for (int i = 0; i < MEMORY_COUNT; i++) {
        cout << "Addr 0x" << setw(2) << hex << i << ": 0x" << (int)memory.getValue(i) << ((i != MEMORY_COUNT - 1) ? "\n" : "");
    }
    cout << setfill('=') << '\n' << right << setw(64) << '=' << "\n\n";

    // Reset cout stream
    cout << left << dec << setfill(' ');
}

bool Interface::askAgain() {
    cout << "Do you want to run another instructions file? (y/n): ";

    while (true) {
        string choice;
        getline(cin, choice);

        if (choice == "y" || choice == "Y") {
            cout << endl;
            return true;
        } else if (choice == "n" || choice == "N") {
            cout <<"Thank you."<< endl;
            return false;
        } else {
            cout << "Invalid input, please enter 'y' or 'n': ";
        }
    }
}
