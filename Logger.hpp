#pragma once

#include <vector>
#include <iostream>

#pragma once

enum class ConsoleColor {
    DEFAULT,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    CYAN,
    MAGENTA,
    WHITE
};


namespace {
    std::string getAnsiCode(ConsoleColor color) {
        switch(color) {
            case ConsoleColor::RED:     return "\033[31m";
            case ConsoleColor::GREEN:   return "\033[32m";
            case ConsoleColor::YELLOW:  return "\033[33m";
            case ConsoleColor::BLUE:    return "\033[34m";
            case ConsoleColor::CYAN:    return "\033[36m";
            case ConsoleColor::MAGENTA: return "\033[35m";
            case ConsoleColor::WHITE:   return "\033[37m";
            default: return "\033[0m"; // Reset / default
        }
    }
}

namespace Logger{
    inline void printColor(const std::string& text, ConsoleColor color) {
        std::cout << getAnsiCode(color) << text << "\033[0m";
    }


    inline void printMap(std::vector<std::vector<int>> mapData, int row, int col) {  
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
                int tile = mapData[i][j];
                switch(tile) {
                    case 0: printColor(" ", ConsoleColor::WHITE); break; // empty
                    case 1: printColor("@", ConsoleColor::RED); break; // central room
                    case 2: printColor("|", ConsoleColor::YELLOW); break; // corridor
                    case 3: printColor("-", ConsoleColor::YELLOW); break; // corridor
                    case 4: printColor("|", ConsoleColor::YELLOW); break; // corridor
                    case 5: printColor("-", ConsoleColor::YELLOW); break; // corridor
                    case 6: printColor("@", ConsoleColor::GREEN); break; // room
                }
            }
            std::cout << std::endl;
        }
    }
}


