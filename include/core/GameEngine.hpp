#pragma once

#include "../map/Map.hpp"
#include "../entities/Player.hpp"
#include "../utils/Utils.hpp"
#include "../utils/Printer.hpp"

#include <cstdlib>

class GameEngine {
private:
    Map* map;
    VECTOR2D mapData;
    int mapDimension;

    Player* player;
    Coords playerMapPosition;

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
            std::cout <<    "======================================\n";
            std::cout <<    "[w]   Walk north\n";
            std::cout <<    "[s]   Walk south\n";
            std::cout <<    "[a]   Walk west\n";
            std::cout <<    "[d]   Walk east\n";
            std::cout <<    "[e]   Interact\n";
            std::cout <<    "\n";
            std::cout <<    "[m]   Open map\n";
            std::cout <<    "[1]   Open menu\n";

            char choice;
            std::cin >> choice;

            // if(!isMapOpened) clearConsole();

            switch(choice) {
                case 'w': movePlayerInRoom(Direction::NORTH); return; break;
                case 's': movePlayerInRoom(Direction::SOUTH); return; break;
                case 'a': movePlayerInRoom(Direction::WEST); return; break;
                case 'd': movePlayerInRoom(Direction::EAST); return; break;
                case 'e': // IMPLEMENT
                    std::cout << "interacted\n";
                    return;
                    break;
                case 'm': // IMPLEMENT
                    isMapOpened = true;
                    printMap();
                    return;
                    break;
                case '1': // IMPLEMENT
                    std::cout << "menu opened\n";
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

        for(int i = 0; i < currentRoomLayout.size(); i++) {
            for(int j = 0; j < currentRoomLayout.size(); j++) {

                if(i == playerCurrentRoomPosition.y && j == playerCurrentRoomPosition.x) {
                    Printer::printColor("@", ConsoleColor::YELLOW);
                    continue;
                }

                RoomTile tile = (RoomTile) currentRoomLayout[i][j];
                switch(tile) {
                    case RoomTile::EMPTY:std:: cout << " "; break;
                    case RoomTile::FLOOR: std::cout << " "; break;
                    case RoomTile::WALL: std::cout << (char) 178; break; // ▓
                    case RoomTile::DOOR: std::cout << "+"; break;
                }
            }
            std::cout << "\n";
        }
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
        std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

    }
};