#pragma once

#include "../map/Map.hpp"
#include "../entities/Player.hpp"
#include "../utils/Utils.hpp"
#include "../utils/Logger.hpp"

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

    ~GameEngine() {
        delete map;
        delete player;
    }

    void start() {
        playerPosition = player->getPosition();
        Logger::printMap(mapData, mapDimension, mapDimension, playerPosition);

        // ========== GAME LOOP ==========
        while(running)
        {
            player->move(chooseMovementDirection());
            playerPosition = player->getPosition();
            Logger::printMap(mapData, mapDimension, mapDimension, playerPosition);
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

    Direction chooseMovementDirection() {
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