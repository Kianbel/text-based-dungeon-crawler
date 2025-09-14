#pragma once

#include "../map/Map.hpp"
#include "../entities/Player.hpp"
#include "../utils/Utils.hpp"
#include "../utils/Logger.hpp"

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
    void initialize() {
        map = new Map();
        map->generateLevel(3);
        mapData = map->getMapData();
        mapDimension = map->getMapDimension();

        player = new Player(mapData, mapDimension);
    }

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
                case 'w':
                    return;
                    break;
                case 's':
                    return;
                    break;
                case 'a':
                    return;
                    break;
                case 'd':
                    return;
                    break;
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

    void movePlayerOnMap(Direction d) { // NOTE: CALL THIS WHEN PLAYER MOVES TO ANOTHER ROOM
        player->moveOnMap(d);
        playerMapPosition = player->getMapPosition();
    }

    // ==================== ROOM LOGIC ====================

    void printCurrentRoom() {
        VECTOR2D currentRoom = map->getCurrentRoom(playerMapPosition);
        srand(0);

        for(int i = 0; i < currentRoom.size(); i++) {
            for(int j = 0; j < currentRoom.size(); j++) {
                RoomTile tile = (RoomTile) currentRoom[i][j];
                int r = rollRandomizedRange(1,100);
                switch(tile) {
                    case RoomTile::EMPTY:
                        std::cout << " ";
                        break;
                    
                    case RoomTile::FLOOR:
                        if(r <= 85) {std::cout << " ";}
                        else {
                            r = rollRandomizedRange(1,2);
                            if(r == 1) std::cout << ".";
                            else std::cout << "_";
                        }
                        break;

                    case RoomTile::WALL:
                        std::cout << (char) 178; // ▓
                        break;

                    case RoomTile::DOOR:
                        std::cout << "+";
                        break;
                }
            }
            std::cout << "\n";
        }
    }

    


    // ==================== HELPER FUNCTIONS ====================

    void printMap() {
        Logger::printMap(mapData, mapDimension, mapDimension, playerMapPosition);
    }

    void clearConsole() {
        for(int i = 0; i < 30; i++) {
            std::cout << '\n';
        }
    }
};