#pragma once

#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

#include "Logger.hpp"

enum class RoomTileType {
    EMPTY = 0,
    CENTER_ROOM = 1,
    NORTH_CORRIDOR = 2,
    EAST_CORRIDOR = 3,
    SOUTH_CORRIDOR = 4,
    WEST_CORRIDOR = 5,
    NORMAL_ROOM = 6
};

typedef struct {
    int x;
    int y;
} RoomCoords;

typedef VECTOR2D VECTOR2D; 

class MapGenerator {
private:
    int mapDimension;
    VECTOR2D mapArr;
    RoomCoords centerRoom;

    int roomAmount;
    int roomGenerationTimeDelay = 100; // in milliseconds

    
public:
    MapGenerator() {
        mapDimension = 11;
        centerRoom = {mapDimension / 2, mapDimension / 2};

        // initialize the map
        mapArr = VECTOR2D(mapDimension, std::vector<int>(mapDimension, 0));
        mapArr[centerRoom.x][centerRoom.y] = RoomTileType::CENTER_ROOM;
    }

    MapGenerator(int mapDimension) {
        this.mapDimension = mapDimension;
        centerRoom = {mapDimension / 2, mapDimension / 2};

        // initialize the map
        mapArr = VECTOR2D(mapDimension, std::vector<int>(mapDimension, 0));
        mapArr[centerRoom.x][centerRoom.y] = RoomTileType::CENTER_ROOM;
    }

    VECTOR2D getMapArr() {return mapArr;}

    int getMapDimension() {return mapDimension;}

    void setRoom(int row, int col, RoomTileType type) {mapArr[row][col] = type;}


    
    void generateLevel(int levelNumber) {
        setRoomAmount(levelNumber);
        // startDunkardWalk();
    }

    

private:
    void moveCurrPos(std::string direction, std::pair<int,int> *currPos) {
        if(direction == "NORTH") {
            currPos->first -= 2;
        }
        else if(direction == "EAST") {
            currPos->second += 2; 
        }
        else if(direction == "SOUTH") {
            currPos->first += 2;
        }
        else if(direction == "WEST") {
            currPos->second -= 2;
        }
        else {
            std::cout << "(var: movCurrPos) INVALID ARGUMENT: movCurrPos must be NORTH/SOUTH/EAST/WEST" << std::endl;
            throw 505;
        }
    }

    void setRoomAmount(int levelNumber) {
        srand(time(0));
        switch(levelNumber) {
            case 1:
                roomAmount = 5 + rand() % 4; // level 1: 5-8 rooms
                break;
            case 2:
                roomAmount = 8 + rand() % 8; // level 2: 8-15 rooms
                break;
            case 3:
                roomAmount = 15 + rand() % 8; // level 3: 15-22 rooms
                break;
            default:
                std::cout << "(var:levelNumber) INVALID INPUT: " << levelNumber << std::endl;
                throw 505;
        }
    }
};