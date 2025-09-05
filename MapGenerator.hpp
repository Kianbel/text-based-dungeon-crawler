#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

#include "Logger.hpp"

enum RoomTileType {
    EMPTY = 0,
    CENTER_ROOM = 1,
    NORTH_CORRIDOR = 2,
    EAST_CORRIDOR = 3,
    SOUTH_CORRIDOR = 4,
    WEST_CORRIDOR = 5,
    NORMAL_ROOM = 6
};


class MapGenerator {
private:
    const int MAP_DIMENSION = 37; // DEFAULT: 11 | MUST BE ODD
    const std::pair<int,int> CENTER_ROOM_INDICES = {MAP_DIMENSION / 2, MAP_DIMENSION / 2}; // first: y | second: x
    
    std::vector<std::vector<int>> mapArr;

    int roomAmount;
    int roomGenerationTimeDelay = 100; // in milliseconds

    
public:
    MapGenerator() {
        mapArr = std::vector<std::vector<int>>(MAP_DIMENSION, std::vector<int>(MAP_DIMENSION, 0));
        mapArr[CENTER_ROOM_INDICES.first][CENTER_ROOM_INDICES.second] = 1; // sets the center of map as starting room (1)
    }
    
    void generateLevel(int levelNumber) {
        setRoomAmount(levelNumber);
        startDunkardWalk();
    }

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

    void startDunkardWalk() {
        const int MAX_ATTEMPTS = 20;

        int roomAmountRemaining = roomAmount;
        std::pair<int,int> currPos = CENTER_ROOM_INDICES;
        int attemptsRemaning = MAX_ATTEMPTS;
        
        srand(time(0));
        while(roomAmountRemaining > 0) {
            auto [currentRow,currentCol] = currPos; // first: row | second: column
            int direction = rand() % 4;

            if(attemptsRemaning <= 0) {break;}

            switch(direction) {
                case 0: // north
                    if(currentRow == 0) break;
                    else if(mapArr[currentRow-1][currentCol] == EMPTY) {
                        if(mapArr[currentRow-2][currentCol] == NORMAL_ROOM || mapArr[currentRow-2][currentCol] == CENTER_ROOM) {
                            setRoom(currentRow-1, currentCol, NORTH_CORRIDOR);
                            moveCurrPos("NORTH", &currPos);
                            attemptsRemaning--;
                        }
                        else {
                            setRoom(currentRow-1, currentCol, NORTH_CORRIDOR);
                            setRoom(currentRow-2, currentCol, NORMAL_ROOM);
                            moveCurrPos("NORTH", &currPos);
                            roomAmountRemaining--;
                            attemptsRemaning = MAX_ATTEMPTS;
                        }
                    }
                    else {
                        attemptsRemaning--;
                    }
                    break;

                case 1: // east
                    if(currentCol == MAP_DIMENSION-1) break;
                    else if(mapArr[currentRow][currentCol+1] == EMPTY) {
                        if(mapArr[currentRow][currentCol+2] == NORMAL_ROOM || mapArr[currentRow][currentCol+2] == CENTER_ROOM) {
                            setRoom(currentRow, currentCol+1, EAST_CORRIDOR);
                            moveCurrPos("EAST", &currPos);
                            attemptsRemaning--;
                        }
                        else {
                            setRoom(currentRow, currentCol+1, EAST_CORRIDOR);
                            setRoom(currentRow, currentCol+2, NORMAL_ROOM);
                            moveCurrPos("EAST", &currPos);
                            roomAmountRemaining--;
                            attemptsRemaning = MAX_ATTEMPTS;
                        }
                    }
                    else {
                        attemptsRemaning--;
                    }
                    break;

                case 2: // south
                    if(currentRow == MAP_DIMENSION-1) break;
                    else if(mapArr[currentRow+1][currentCol] == EMPTY) {
                        if(mapArr[currentRow+2][currentCol] == NORMAL_ROOM || mapArr[currentRow+2][currentCol] == CENTER_ROOM) {
                            setRoom(currentRow+1, currentCol, SOUTH_CORRIDOR);
                            moveCurrPos("SOUTH", &currPos);
                            attemptsRemaning--;
                        }
                        else {
                            setRoom(currentRow+1, currentCol, SOUTH_CORRIDOR);
                            setRoom(currentRow+2, currentCol, NORMAL_ROOM);
                            moveCurrPos("SOUTH", &currPos);
                            roomAmountRemaining--;
                            attemptsRemaning = MAX_ATTEMPTS;
                        }
                    }
                    else {
                        attemptsRemaning--;
                    }
                    break;

                case 3: // west
                    if(currentCol == 0) break;
                    else if(mapArr[currentRow][currentCol-1] == EMPTY) {
                        if(mapArr[currentRow][currentCol-2] == NORMAL_ROOM || mapArr[currentRow][currentCol-2] == CENTER_ROOM) {
                            setRoom(currentRow, currentCol-1, WEST_CORRIDOR);
                            moveCurrPos("WEST", &currPos);
                            attemptsRemaning--;
                        }
                        else {
                            setRoom(currentRow, currentCol-1, WEST_CORRIDOR);
                            setRoom(currentRow, currentCol-2, NORMAL_ROOM);
                            moveCurrPos("WEST", &currPos);
                            roomAmountRemaining--;
                            attemptsRemaning = MAX_ATTEMPTS;
                        }
                    }
                    else {
                        attemptsRemaning--;
                    }
                    break;
            }
        }
    
        Logger::printMap(mapArr, MAP_DIMENSION, MAP_DIMENSION, currPos);
    }   
    
    // ========================================================
  
    // GETTERS
    std::vector<std::vector<int>> getMapArr() {return mapArr;}
    int getMapDimension() {return MAP_DIMENSION;}

    // SETTERS
    void setRoom(int row, int col, RoomTileType type) {mapArr[row][col] = type;}

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