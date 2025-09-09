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

public:
    GameEngine() {
        intialize();
    }

    ~GameEngine() {
        delete map;
        delete player;
    }

    void start() {
        playerMapPosition = player->getMapPosition();
        Logger::printMap(mapData, mapDimension, mapDimension, playerMapPosition);

        // ========== GAME LOOP ==========
        while(isRunning)
        {
            if(!hasPlayerMovedRoom) {

            }
            else {
                movePlayerOnMap();
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

    void movePlayerOnMap() {
        player->moveOnMap(chooseMovementDirection()); // REFACTOR
        playerMapPosition = player->getMapPosition();
        Logger::printMap(mapData, mapDimension, mapDimension, playerMapPosition);
    }

    Direction chooseMovementDirection() { // REFACTOR SINCE THIS IS MAP MOVEMENT, NOT ROOM MOVEMENT
        char c;
        while(true) {
            std::cout << "\nWhich direction do you want to go? (w/a/s/d): ";
            std::cin >> c;
            c = tolower(c);
            switch(c) {
                case 'w':
                    return Direction::NORTH;
                case 's':
                    return Direction::SOUTH;
                case 'd':
                    return Direction::EAST;
                case 'a':
                    return Direction::WEST;
                default:
                    std::cout << "\nInvalid direction";
            }
        }
    }
};