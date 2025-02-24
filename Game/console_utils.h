#pragma once

#include <windows.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <conio.h>

inline void SetCursorPosition(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorPosition = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	SetConsoleCursorPosition(consoleHandle, cursorPosition);
}


inline void PrintSpriteAt(int x, int y, const std::string& sprite) {
	SetCursorPosition(x, y);
	int startX = x; // Store original X position
	int row = 0;    // Track current row

	std::string line;
	for (char c : sprite) {
		if (c == '\n') {
			row++;  // Move down one row
			SetCursorPosition(startX, y + row); // Reset X, go to next line
		}
		else {
			std::cout << c;
		}
	}
}


inline void HideCursor() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(consoleHandle, &cursorInfo);
	cursorInfo.bVisible = FALSE; // Hide cursor
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

