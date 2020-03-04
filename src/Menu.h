#pragma once
#include <iostream>
#include <fstream>
#include "DoublyList.h"

void save(DoublyList<int>& list, const std::string& fileName) {
	std::ofstream outFile(fileName);

	while (!outFile.is_open()) {
		std::cout << "File didn't open, give me just a bit\n";
		outFile.open(fileName, std::ios::out);
	}

	DoublyList<int>::Iterator it = list.getTail();

	while (it) {
		outFile << it->value << " ";
		it = it->next;
	}

	outFile.close();
	std::cout << "List saved to file!\n";
}

void load(DoublyList<int>& list, const std::string fileName) {
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
		list.pushToHead(data);

	inFile.close();
	std::cout << "List created from file!\n";
}

void choice(const int& c, DoublyList<int>& list) {
	system("clear");

	switch (c) {
		case 0: {
			std::cout << std::endl;
			DoublyList<int>::Iterator it = list.getTail();
			while (it) {
				std::cout << list.getValue(it) << " ";
				it = list.getNext(it);
			}
			std::cout << std::endl;
			break;
		}

		case 1: {
			int value;
			std::cout << "Enter value: ";
			std::cin >> value;
			list.pushToHead(value);
			break;
		}

		case 2: {
			int value;
			std::cout << "Enter value: ";
			std::cin >> value;
			list.pushToTail(value);
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
			list.clear();
			std::cout << "List cleared\n";
			break;
		}

		case 6: {
			if (list.isEmpty())
				std::cout << "List is empty\n";
			else
				std::cout << "List is not empty\n";
			break;
		}

		case 7: {
			std::string fileName;
			std::cout << "Enter filename: ";
			std::cin >> fileName;
			save(list, fileName);
			break;
		}

		case 8: {
			std::string fileName;
			std::cout << "Enter filename: ";
			std::cin >> fileName;
			load(list, fileName);
			break;
		}
	}
}

void menu(DoublyList<int>& list) {
	int c;
	while (true) {
		std::cout << "Options:\n\n";
		std::cout << "0. Print list\n";
		std::cout << "1. Push element after head\n";
		std::cout << "2. Push element before tail\n";
		std::cout << "3. Push element after position\n";
		std::cout << "4. Pop element on position\n";
		std::cout << "5. Clear list\n";
		std::cout << "6. Check if empty\n";
		std::cout << "7. Save to file\n";
		std::cout << "8. Read from file\n";

		std::cin >> c;

		choice(c, list);
	}
}
