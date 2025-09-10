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
    bool hasPlayerMovedRoom = true;

public:
    GameEngine() {
        intialize();
    }

    ~GameEngine() {
        delete map;
        delete player;
    }

    void start() {
        // INITIALIZATIONS
        playerMapPosition = player->getMapPosition();


        // ========== GAME LOOP ==========
        while(isRunning)
        {
            clearConsole();
            showChoiceOptions();

            if(!hasPlayerMovedRoom) {
                
            }
            else {
                
            }
        }
        // ========== END GAME LOOP ==========

    }

private:
    void intialize() {
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
            clearConsole();

            switch(choice) {
                case 'w':
                    break;
                case 's':
                    break;
                case 'a':
                    break;
                case 'd':
                    break;
                case 'e': // IMPLEMENT
                    std::cout << "interacted\n";
                    break;
                case 'm': // IMPLEMENT

                    printMap();
                    std::cout << "map opened\n";
                    break;
                case '1': // IMPLEMENT
                    std::cout << "menu opened\n";
                    break;
                default:
                    std::cout << "Invalid choice [" << choice << "], try again.\n";
                    break;
            }
        }
    }

    void movePlayerOnMap(Direction d) { // NOTE: CALL THIS WHEN PLAYER MOVES TO ANOTHER ROOM
        player->moveOnMap(d);
        playerMapPosition = player->getMapPosition();
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