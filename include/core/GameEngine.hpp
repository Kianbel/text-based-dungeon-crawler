#pragma once

#include "../map/Map.hpp"
#include "../entities/Player.hpp"
#include "../utils/Utils.hpp"
#include "../utils/Printer.hpp"

#include <cstdlib>
#include <conio.h> // getch() to automatically read the input without needing to press the 'Enter' key
#include <windows.h> // for no flickering when clearing the console in the clearConsole() function
#include <string>

class GameEngine {
private:
    Map* map;
    VECTOR2D mapData;
    int mapDimension;

    Player* player;
    Coords playerMapPosition;

    std::string dialogueMessage = "What would you like to do? \n";

    bool isRunning = true;
    bool hasPlayerMovedRoom = false;
    bool isMapOpened = false;

public:
    GameEngine() {
        initialize();
    }

    ~GameEngine() {
        delete map;
        delete player;
    }

    void start() {
        // INITIALIZATIONS
        playerMapPosition = player->getMapPosition();
        


        // ========== GAME LOOP ==========
        while(isRunning) {         
            clearConsole();

            if(!hasPlayerMovedRoom) {

                // PRINT MAP OR CURRENT ROOM
                if(!isMapOpened) printCurrentRoom();
                else {printMap(); isMapOpened = false;}
            }
            else {
                
            }

            showChoiceOptions();
        }
        // ========== END GAME LOOP ==========

    }
private:
    void showChoiceOptions() {
        while(true) {
            std::cout <<    "\n";
            std::cout <<    "======================================\n";
            std::cout <<    dialogueMessage;
            std::cout <<    "======================================\n";
            std::cout <<    "   [w]   Walk north\n";
            std::cout <<    "   [s]   Walk south\n";
            std::cout <<    "   [a]   Walk west\n";
            std::cout <<    "   [d]   Walk east\n";
            std::cout <<    "   [e]   Interact\n";
            std::cout <<    "\n";
            std::cout <<    "   [m]   Open map\n";
            std::cout <<    "   [1]   Open menu\n";
            std::cout <<    "\n";
            std::cout <<    "   [x]   Quit\n";

            char choice;
            choice = _getch();



            switch(choice) {
                case 'w': movePlayerInRoom(Direction::NORTH); return; break;
                case 's': movePlayerInRoom(Direction::SOUTH); return; break;
                case 'a': movePlayerInRoom(Direction::WEST); return; break;
                case 'd': movePlayerInRoom(Direction::EAST); return; break;
                case 'e': // IMPLEMENT
                    std::cout << "interacted\n";
                    return;
                    break;
                case 'm':
                    isMapOpened = true;
                    printMap();
                    return;
                    break;
                case '1': // IMPLEMENT
                    std::cout << "menu opened\n";
                    return;
                    break;
                case 'x':
                    clearConsole();
                    std::cout << "game ended";
                    isRunning = false;
                    return;
                    break;
                default:
                    std::cout << "Invalid choice [" << choice << "], try again.\n";
                    return;
                    break;
            }
        }
    }

    // ==================== MAP AND ROOM LOGIC ====================

    void printCurrentRoom() {
        RoomDetails currentRoomDetails = map->getCurrentRoomDetails(playerMapPosition);
        VECTOR2D currentRoomLayout = currentRoomDetails.roomLayout;
        Coords playerCurrentRoomPosition = currentRoomDetails.playerCoords;

        std::string printOutput;

        for(int i = 0; i < currentRoomLayout.size(); i++) {
            for(int j = 0; j < currentRoomLayout.size(); j++) {

                if(i == playerCurrentRoomPosition.y && j == playerCurrentRoomPosition.x) {
                    // Printer::printColor("@", ConsoleColor::YELLOW);
                    printOutput.push_back('@');
                    continue;
                }

                RoomTile tile = (RoomTile) currentRoomLayout[i][j];
                switch(tile) {
                    case RoomTile::EMPTY: printOutput.push_back(' '); break;
                    case RoomTile::FLOOR: printOutput.push_back(' '); break;
                    case RoomTile::WALL: printOutput.push_back((char) 178); break; // ▓
                    case RoomTile::DOOR: printOutput.push_back('+'); break;
                }
            }
            printOutput.push_back('\n');
        }

        std::cout << printOutput;
    }

    void movePlayerOnMap(Direction direction) { // NOTE: CALL THIS WHEN PLAYER MOVES TO ANOTHER ROOM
        player->moveOnMap(direction);
        playerMapPosition = player->getMapPosition();
    }

    void movePlayerInRoom(Direction direction) {
        RoomDetails& currentRoom = map->getCurrentRoomDetails(playerMapPosition);
        std::cout << currentRoom.playerCoords.x << "," << currentRoom.playerCoords.y << std::endl;
        player->moveInRoom(direction, currentRoom);
    }
    
    // ==================== HELPER FUNCTIONS ====================

    void initialize() {
        map = new Map();
        map->generateLevel(3);
        mapData = map->getMapData();
        mapDimension = map->getMapDimension();

        player = new Player(mapData, mapDimension);
    }

    void printMap() {
        Printer::printMap(mapData, mapDimension, mapDimension, playerMapPosition);
    }

    void clearConsole() {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD coordScreen = { 0, 0 };
        DWORD cCharsWritten;
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        DWORD dwConSize;

        // Get buffer size
        if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
            return;
        dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

        // Fill screen with spaces
        FillConsoleOutputCharacter(hConsole, ' ', dwConSize, coordScreen, &cCharsWritten);

        // Reset attributes
        FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);

        // Move cursor back to top-left
        SetConsoleCursorPosition(hConsole, coordScreen);
    }
};