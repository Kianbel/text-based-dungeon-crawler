#pragma once

#include "Map.hpp"
#include "Player.hpp"
#include "Utils.hpp"
#include "Logger.hpp"

#include <cstdlib>

class GameEngine {
private:
    Map* map;
    int mapDimension;
    Player* player;
    Coords playerPosition;
    VECTOR2D mapData;

    bool running = true;

public:
    GameEngine() {
        intialize();
    }

    void start() {
        while(running) {
            player->move(chooseMovementDirection());
            playerPosition = player->getPosition();
            Logger::printMap(mapData, mapDimension, mapDimension, playerPosition);
        }
    }

private:
    void intialize() {
        map = new Map();
        map->generateLevel(1);
        mapData = map->getMapData();
        mapDimension = map->getMapDimension();

        player = new Player(mapData, mapDimension);
    }

    Direction chooseMovementDirection() {
        char c;
        while(true) {
            std::cout << "\nWhich direction do you want to go? (n/s/e/w): ";
            std::cin >> c;
            c = tolower(c);
            switch(c) {
                case 'n':
                    return Direction::NORTH;
                case 's':
                    return Direction::SOUTH;
                case 'e':
                    return Direction::EAST;
                case 'w':
                    return Direction::WEST;
                default:
                    std::cout << "\nInvalid direction";
            }
        }
    }
};