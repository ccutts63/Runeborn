#pragma once
#include <iostream>
#include "console_utils.h"
#include <sstream>
#include <cstdio>
#include <conio.h>
#include <thread>
#include <chrono>



// Convert any type to a string
template <typename T>
std::string ToString(const T& value) {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

// Print text slowly (helper function)
inline void SlowPrintHelper(const std::string& text) {
    for (char c : text) {
        std::cout << c << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Adjust speed
    }
    
}

inline void WaitForUser() {

    // Clear any remaining keypresses in the buffer before starting
    while (_kbhit()) {
        _getch();  // Discard any previous keys in the buffer
    }

    while (true) {
        std::cout << "\033[34;44mV\033[0m";  // Blue text on blue background
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "\b \b";  // Erase character
        std::cout << "\033[34;47mV\033[0m";  // Blue text on white background
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        if (_kbhit()) {  // If a key is pressed, break the loop
            _getch();  // Consume the first keypress

            break;  // Exit after processing the first keypress
        }

        std::cout << "\b \b";  // Erase character

    }

    SetCursorPosition(2, 26);
    std::cout << "                                          ";
    SetCursorPosition(2, 26);
}

// Base case (stops recursion)
inline void SlowPrint() {
    // Just end recursion
    WaitForUser();
}

// Variadic template function for multiple arguments
template <typename First, typename... Rest>
inline void SlowPrint(First&& first, Rest&&... rest) {

    // Print first argument
    SlowPrintHelper(ToString(first));

    // Recursively print the rest
    SlowPrint(std::forward<Rest>(rest)...);

}

