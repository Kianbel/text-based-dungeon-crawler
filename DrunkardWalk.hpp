#pragma once

#include <MapGenerator.hpp>

class DrunkardWalk : public MapGenerator {
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
};
