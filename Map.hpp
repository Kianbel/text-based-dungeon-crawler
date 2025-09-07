#pragma once

#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Utils.hpp"
#include "ProbabilityUtils.hpp"
#include "DrunkardWalk.hpp"
#include "Room.hpp"

class Map {
private:
    int mapDimension;
    VECTOR2D mapData;
    Coords centerRoom;

    int roomAmount;
    int levelNumber;
    
public:
    Map() {
        mapDimension = 11;
        centerRoom = {mapDimension / 2, mapDimension / 2};

        // initialize the map
        mapData = VECTOR2D(mapDimension, std::vector<int>(mapDimension, 0));
        mapData[centerRoom.x][centerRoom.y] = (int) RoomTileType::CENTER_ROOM;
    }

    Map(int mapDimension) {
        this->mapDimension = mapDimension;
        centerRoom = {mapDimension / 2, mapDimension / 2};

        // initialize the map
        mapData = VECTOR2D(mapDimension, std::vector<int>(mapDimension, 0));
        mapData[centerRoom.x][centerRoom.y] = (int) RoomTileType::CENTER_ROOM;
    }

    // ------------------------- LOGIC ---------------------------

    void generateLevel(int levelNumber) {       
        setRoomAmount(levelNumber);
        this->levelNumber = levelNumber;

        DrunkardWalk dWalk;
        dWalk.startDrunkardWalk(mapData, roomAmount, mapDimension);

        // =========== TEMPORARY =======================
        for(int i = 0 ; i < roomAmount; i++) {
            Room room;
            PAIR_INT r = room.generateRoom();
            std::cout << "Room " << i << ": {size: " << r.first << "| variant: " << r.second << "} \n";
        }
    }

    // -------------------- SETTERS / GETTERS -------------------- 

    VECTOR2D getMapData() {return mapData;}

    int getMapDimension() {return mapDimension;}

    int getRoomAmount() {return roomAmount;}

    void setRoom(int row, int col, RoomTileType type) {mapData[row][col] = (int) type;}

    // ------------------- UNDERLYING FUNCTIONS ------------------

private:
    void setRoomAmount(int levelNumber) {
        switch(levelNumber) {
            case 1:
                roomAmount = rollRandomizedRange(5, 8);
                break;
            case 2:
                roomAmount = rollRandomizedRange(8, 12);
                break;
            case 3:
                roomAmount = rollRandomizedRange(12, 22);
                break;
            default:
                std::cout << "(var:levelNumber) INVALID INPUT: " << levelNumber << std::endl;
                throw 505;
        }
    }
};