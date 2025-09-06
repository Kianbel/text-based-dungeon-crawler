#pragma once

#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Utils.hpp"
#include "DrunkardWalk.hpp"
#include "Room.hpp"

using std::cout;
using std::endl;

class MapGenerator {
private:
    int mapDimension;
    VECTOR2D mapArr;
    Coords centerRoom;

    int roomAmount;
    int levelNumber;
    
public:
    MapGenerator() {
        mapDimension = 11;
        centerRoom = {mapDimension / 2, mapDimension / 2};

        // initialize the map
        mapArr = VECTOR2D(mapDimension, std::vector<int>(mapDimension, 0));
        mapArr[centerRoom.x][centerRoom.y] = (int) RoomTileType::CENTER_ROOM;
    }

    MapGenerator(int mapDimension) {
        this->mapDimension = mapDimension;
        centerRoom = {mapDimension / 2, mapDimension / 2};

        // initialize the map
        mapArr = VECTOR2D(mapDimension, std::vector<int>(mapDimension, 0));
        mapArr[centerRoom.x][centerRoom.y] = (int) RoomTileType::CENTER_ROOM;
    }

    // -------------------- SETTERS / GETTERS -------------------- 

    VECTOR2D* getMapArrPtr() {return &mapArr;}

    int getMapDimension() {return mapDimension;}

    int getRoomAmount() {return roomAmount;}

    void setRoom(int row, int col, RoomTileType type) {mapArr[row][col] = (int) type;}

    // ------------------------- LOGIC ---------------------------

    void generateLevel(int levelNumber) {       
        setRoomAmount(levelNumber);
        this->levelNumber = levelNumber;

        DrunkardWalk dWalk;
        dWalk.startDrunkardWalk(&mapArr, roomAmount, mapDimension);

        for(int i = 0 ; i < roomAmount; i++) {
            Room room;
            PAIR_INT r = room.generateRoom();
            cout << "Room " << i << ": {size: " << r.first << "| variant: " << r.second << "}" << endl;
        }
    }

    // ------------------- UNDERLYING FUNCTIONS ------------------

protected:
    void setRoomAmount(int levelNumber) {
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