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

#include "Map.hpp"
#include <iostream>

bool gameRunning = 0;

int main() {
    srand(time(0)); // initialize randomness

    Map map;
    map.generateLevel(1);

    while(gameRunning) {
        gameLoop();
    }

    return 0;
}

void gameLoop() {
    
}

