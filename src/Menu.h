#pragma once
#include <iostream>
#include <fstream>
#include "DoublyList.h"

/* A universal way to clear console screen without using system calls */
#ifdef _WIN32
#include <windows.h>
void clearScreen() {
    HANDLE                     hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD                      count;
    DWORD                      cellCount;
    COORD                      homeCoords = { 0, 0 };

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE) return;

    /* Get the number of cells in the current buffer */
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(
        hStdOut,
        (TCHAR)' ',
        cellCount,
        homeCoords,
        &count
    )) return;

/* Fill the entire buffer with the current colors and attributes */
    if (!FillConsoleOutputAttribute(
        hStdOut,
        csbi.wAttributes,
        cellCount,
        homeCoords,
        &count
    )) return;

/* Move the cursor home */
    SetConsoleCursorPosition(hStdOut, homeCoords);
}
#endif

#ifdef __unix__
#include <unistd.h>
#include <term.h>

void clearScreen() {
    if (!cur_term) {
        int result;
        setupterm(NULL, STDOUT_FILENO, &result);
        if (result <= 0) return;
    }

    putp(tigetstr("clear"));
}
#endif

void save(DoublyList<int> &list, const std::string &fileName) {
    std::ofstream outFile(fileName);

    while (!outFile.is_open()) {
        std::cout << "File didn't open, give me just a bit\n";
        outFile.open(fileName, std::ios::out);
    }

    DoublyList<int>::Iterator it = list.getHead();

    while (it) {
        outFile << it->value << " ";
        it = it->next;
    }

    outFile.close();
    std::cout << "List saved to file!\n";
}

void load(DoublyList<int> &list, const std::string fileName) {
    std::ifstream inFile(fileName);

    int i = 0;
    while (!inFile.is_open()) {
        if (i > 2) {
            std::cout << "File failed to open, probably not found, idk\n";
            return;
        }
        std::cout << "File didn't open, give me just a bit\n";
        inFile.open(fileName, std::ios::in);
        ++i;
    }

    if (!list.isEmpty()) list.clear();

    int data;
    while (inFile >> data)
        list.pushToTail(data);

    inFile.close();
    std::cout << "List created from file!\n";
}

void choice(const int &c, DoublyList<int> &list) {
    clearScreen();

    switch (c) {
        case 0: {
            if (list.isEmpty())
                std::cout << "List is empty\n";
            else {
                DoublyList<int>::Iterator it = list.getHead();
                while (it) {
                    std::cout << list.getValue(it) << " ";
                    it = list.getNext(it);
                }
                std::cout << std::endl;
            }
            break;
        }

        case 1: {
            int value;
            std::cout << "Enter value: ";
            std::cin >> value;
            list.pushToTail(value);
            break;
        }

        case 2: {
            int value;
            std::cout << "Enter value: ";
            std::cin >> value;
            list.pushToHead(value);
            break;
        }

        case 3: {
            int value, pos;
            std::cout << "Enter value and position: ";
            std::cin >> value >> pos;
            list.pushAfter(value, pos);
            break;
        }

        case 4: {
            int position;
            std::cout << "Select element position: ";
            std::cin >> position;
            std::cout << "Popped value " << list.pop(--position) << std::endl;
            break;
        }

        case 5: {
            if (list.isEmpty())
                std::cout << "List is empty\n";
            else {
                list.sort();
                std::cout << "List sorted!\n";
            }
            break;
        }

        case 6: {
            list.clear();
            std::cout << "List cleared\n";
            break;
        }

        case 7: {
            if (list.isEmpty())
                std::cout << "List is empty\n";
            else
                std::cout << "List is not empty\n";
            break;
        }

        case 8: {
            std::string fileName;
            std::cout << "Enter filename: ";
            std::cin >> fileName;
            save(list, fileName);
            break;
        }

        case 9: {
            std::string fileName;
            std::cout << "Enter filename: ";
            std::cin >> fileName;
            load(list, fileName);
            break;
        }
    }
}

void menu(DoublyList<int> &list) {
    int c;
    while (true) {
        std::cout << "Options:\n\n";
        std::cout << "0. Print list\n";
        std::cout << "1. Push element to end\n";
        std::cout << "2. Push element to beginning\n";
        std::cout << "3. Push element after position\n";
        std::cout << "4. Pop element on position\n";
        std::cout << "5. Sort list\n";
        std::cout << "6. Clear list\n";
        std::cout << "7. Check if empty\n";
        std::cout << "8. Save to file\n";
        std::cout << "9. Read from file\n";

        std::cin >> c;

        choice(c, list);
    }
}
