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

inline void SetConsoleSize(int width, int height) {
	// Get the console handle
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Set the screen buffer size
	COORD bufferSize = { static_cast<SHORT>(width), static_cast<SHORT>(height) };
	SetConsoleScreenBufferSize(hConsole, bufferSize);

	// Set the console window size
	SMALL_RECT windowSize = { 0, 0, static_cast<SHORT>(width - 1), static_cast<SHORT>(height - 1) };
	SetConsoleWindowInfo(hConsole, TRUE, &windowSize);
}

inline void SetConsoleAppearance() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Change console font to Raster Fonts (12x16)
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 18; // Width
	cfi.dwFontSize.Y = 18; // Height
	cfi.FontFamily = 0; // 0 = Raster Fonts
	cfi.FontWeight = 10; // Normal weight
	wcscpy_s(cfi.FaceName, L"Terminal"); // Set to Raster Font (Terminal)

	SetCurrentConsoleFontEx(hConsole, FALSE, &cfi);
}

