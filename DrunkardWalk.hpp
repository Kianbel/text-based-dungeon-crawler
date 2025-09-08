#pragma once

#include "Utils.hpp"
#include "Logger.hpp"
#include "ProbabilityUtils.hpp"

class DrunkardWalk {
private:
    const int MAX_ATTEMPTS = 8;
    int roomAmountRemaining;
    int attemptsRemaining;
    Coords currPos;

public:
    void startDrunkardWalk(VECTOR2D& mapData, int roomAmount, int mapDimension) {
        // cout << "Starting Drunkard's Walk Algorithm..." << endl;

        roomAmountRemaining = roomAmount;
        attemptsRemaining = MAX_ATTEMPTS;
        currPos = {mapDimension / 2, mapDimension / 2};

        Direction prevDirection;

        while(roomAmountRemaining > 0) {
            int direction = rollRandomizedRange(0, 4);

            if(attemptsRemaining <= 0) break;

            switch(direction) {
                case (int) Direction::NORTH:
                    if(currPos.y <= 1 || direction == (int) Direction::SOUTH) break;
                    else if(mapData[currPos.y-1][currPos.x] == (int) RoomTileType::EMPTY) {
                        if(mapData[currPos.y-2][currPos.x] == (int) RoomTileType::NORMAL_ROOM || mapData[currPos.y-2][currPos.x] == (int) RoomTileType::CENTER_ROOM) {
                            setRoom(currPos.y-1, currPos.x, RoomTileType::VERTICAL_CORRIDOR, mapData);
                            moveCurrPos(Direction::NORTH, currPos);
                            prevDirection = Direction::SOUTH;
                            attemptsRemaining--;
                        }
                        else {
                            setRoom(currPos.y-1, currPos.x, RoomTileType::VERTICAL_CORRIDOR, mapData);
                            setRoom(currPos.y-2, currPos.x, RoomTileType::NORMAL_ROOM, mapData);
                            moveCurrPos(Direction::NORTH, currPos);
                            prevDirection = Direction::SOUTH;
                            roomAmountRemaining--;
                            attemptsRemaining = MAX_ATTEMPTS;
                        }
                    }
                    else {
                        attemptsRemaining--;
                    }
                    break;

                case (int) Direction::EAST:
                    if(currPos.x >= mapDimension-2 || direction == (int) Direction::WEST) break;
                    else if(mapData[currPos.y][currPos.x+1] == (int) RoomTileType::EMPTY) {
                        if(mapData[currPos.y][currPos.x+2] == (int) RoomTileType::NORMAL_ROOM || mapData[currPos.y][currPos.x+2] == (int) RoomTileType::CENTER_ROOM) {
                            setRoom(currPos.y, currPos.x+1, RoomTileType::HORIZONTAL_CORRIDOR, mapData);
                            moveCurrPos(Direction::EAST, currPos);
                            prevDirection = Direction::WEST;
                            attemptsRemaining--;
                        }
                        else {
                            setRoom(currPos.y, currPos.x+1, RoomTileType::HORIZONTAL_CORRIDOR, mapData);
                            setRoom(currPos.y, currPos.x+2, RoomTileType::NORMAL_ROOM, mapData);
                            moveCurrPos(Direction::EAST, currPos);
                            prevDirection = Direction::WEST;
                            roomAmountRemaining--;
                            attemptsRemaining = MAX_ATTEMPTS;
                        }
                    }
                    else {
                        attemptsRemaining--;
                    }
                    break;

                case (int) Direction::SOUTH:
                    if(currPos.y >= mapDimension-2 || direction == (int) Direction::NORTH) break;
                    else if(mapData[currPos.y+1][currPos.x] == (int) RoomTileType::EMPTY) {
                        if(mapData[currPos.y+2][currPos.x] == (int) RoomTileType::NORMAL_ROOM || mapData[currPos.y+2][currPos.x] == (int) RoomTileType::CENTER_ROOM) {
                            setRoom(currPos.y+1, currPos.x, RoomTileType::VERTICAL_CORRIDOR, mapData);
                            moveCurrPos(Direction::SOUTH, currPos);
                            prevDirection = Direction::NORTH;
                            attemptsRemaining--;
                        }
                        else {
                            setRoom(currPos.y+1, currPos.x, RoomTileType::VERTICAL_CORRIDOR, mapData);
                            setRoom(currPos.y+2, currPos.x, RoomTileType::NORMAL_ROOM, mapData);
                            moveCurrPos(Direction::SOUTH, currPos);
                            prevDirection = Direction::NORTH;
                            roomAmountRemaining--;
                            attemptsRemaining = MAX_ATTEMPTS;
                        }
                    }
                    else {
                        attemptsRemaining--;
                    }
                    break;

                case (int) Direction::WEST:
                    if(currPos.x <= 1 || direction == (int) Direction::EAST) break;
                    else if(mapData[currPos.y][currPos.x-1] == (int) RoomTileType::EMPTY) {
                        if(mapData[currPos.y][currPos.x-2] == (int) RoomTileType::NORMAL_ROOM || mapData[currPos.y][currPos.x-2] == (int) RoomTileType::CENTER_ROOM) {
                            setRoom(currPos.y, currPos.x-1, RoomTileType::HORIZONTAL_CORRIDOR, mapData);
                            moveCurrPos(Direction::WEST, currPos);
                            prevDirection = Direction::EAST;
                            attemptsRemaining--;
                        }
                        else {  
                            setRoom(currPos.y, currPos.x-1, RoomTileType::HORIZONTAL_CORRIDOR, mapData);
                            setRoom(currPos.y, currPos.x-2, RoomTileType::NORMAL_ROOM, mapData);
                            moveCurrPos(Direction::WEST, currPos);
                            prevDirection = Direction::EAST;
                            roomAmountRemaining--;
                            attemptsRemaining = MAX_ATTEMPTS;
                        }
                    }
                    else {
                        attemptsRemaining--;
                    }
                    break;
            }
        }
    
        // Logger::printMap(mapData, mapDimension, mapDimension);
    }
    
private:
    void moveCurrPos(Direction direction, Coords& currPos) {
        if(direction == Direction::NORTH) {
            currPos.y -= 2;
        }
        else if(direction == Direction::EAST) {
            currPos.x += 2; 
        }
        else if(direction == Direction::SOUTH) {
            currPos.y += 2;
        }
        else if(direction == Direction::WEST) {
            currPos.x -= 2;
        }
        else {
            std::cout << "(var: movCurrPos) INVALID ARGUMENT: movCurrPos must be NORTH/SOUTH/EAST/WEST" << std::endl;
            throw 505;
        }
    }

    void setRoom(int row, int col, RoomTileType type, VECTOR2D& mapData) {
        mapData[row][col] = (int) type;
    }
};
