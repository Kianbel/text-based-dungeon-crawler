#pragma once

#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "../utils/Utils.hpp"
#include "../utils/ProbabilityUtils.hpp"
#include "../utils/Logger.hpp"
#include "DrunkardWalk.hpp"
#include "Room.hpp"

struct RoomDetails {
    Coords coords;
    VECTOR2D layout;
};


class Map {
private:
    int mapDimension;
    VECTOR2D mapData;
    Coords centerRoom;
    std::vector<RoomDetails> rooms;

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

        generateRooms();
        
    }

    void printMap() {
        Logger::printMap(mapData, mapDimension, mapDimension);
    }


    // -------------------- SETTERS / GETTERS -------------------- 

    VECTOR2D getMapData() {return mapData;}

    int getMapDimension() {return mapDimension;}

    int getRoomAmount() {return roomAmount;}

    void setRoom(int row, int col, RoomTileType type) {mapData[row][col] = (int) type;}

    // ------------------- UNDERLYING FUNCTIONS ------------------

private:
    void generateRooms() {        
        for(int i = 0; i < mapDimension; i++) {
            for(int j = 0; j < mapDimension; j++) {
                if(mapData[i][j] == (int) RoomTileType::CENTER_ROOM || mapData[i][j] == (int) RoomTileType::NORMAL_ROOM) {
                    Room room;
                    
                    RoomDetails r;
                    r.coords = {j, i};
                    r.layout = room.getRoomData();

                    rooms.push_back(r);
                }
            }
        }

        // for(auto& r : rooms) {
        //     std::cout << "x=" << r.coords.x << ", y=" << r.coords.y << "\n";
        // }
    }

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