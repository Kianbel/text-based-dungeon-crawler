/*
    DATE: 8/27/25
    GAME DESCRIPTION:
        text-based dungeon crawler

    CHECKLIST:
        - dungeon map generator
            - randomized/procedural room layout
            - random loot
            - boss rooms
            - different levels to the dungeon  
                > the deeper the level, the harder
*/

#include "MapGenerator.hpp"
#include <iostream>

int main() {
    srand(time(0));
    MapGenerator* map = new MapGenerator();
    map->generateLevel(2);

    delete map;

    return 0;
}

