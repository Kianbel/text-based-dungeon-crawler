#pragma once

// this is a player

#include "../map/Map.hpp"
#include "../utils/Utils.hpp"

class Player {
private:
    VECTOR2D mapData;

    Coords mapPosition;
    Coords roomPosition;
    int health;
    int armor;

public:
    Player(VECTOR2D& mapData, int mapDimension) {
        this->mapData = mapData;
        this->mapPosition = {mapDimension/2 , mapDimension/2};
        health = 100;
        armor = 0;
    }

    void foo() {
        std::cout << "hello world" << std::endl;
    }

    void moveOnMap(Direction direction) {
        std::cout << "\nPlayer x,y: {" << mapPosition.x << "," << mapPosition.y << "}\n";

        switch((int) direction) {
            case (int) Direction::NORTH:
                if(mapData[mapPosition.y-1][mapPosition.x] == (int) MapTile::VERTICAL_CORRIDOR) {
                    mapPosition.y -= 2;
                }
                else {
                    std::cout << "Player can't go north, something's blocking the way.\n";
                }
                break;
            case (int) Direction::EAST:
                if(mapData[mapPosition.y][mapPosition.x+1] == (int) MapTile::HORIZONTAL_CORRIDOR) {
                    mapPosition.x += 2;
                }
                else {
                    std::cout << "Player can't go east, something's blocking the way.\n";
                }
                break;
            case (int) Direction::SOUTH:
                if(mapData[mapPosition.y+1][mapPosition.x] == (int) MapTile::VERTICAL_CORRIDOR) {
                    mapPosition.y += 2;
                }
                else {
                    std::cout << "Player can't go south, something's blocking the way.\n";
                }
                break;
            case (int) Direction::WEST:
                if(mapData[mapPosition.y][mapPosition.x-1] == (int) MapTile::HORIZONTAL_CORRIDOR) {
                    mapPosition.x -= 2;
                }
                else {
                    std::cout << "Player can't go west, something's blocking the way.\n";
                }
                break;
            default:
                std::cout << "Player can't move in an invalid direction.\n";
                break;
        }
    }

    void moveInRoom(Direction direction, RoomDetails& currentRoom) {
        VECTOR2D& roomLayout = currentRoom.roomLayout;
        Coords& playerCoords = currentRoom.playerCoords;
        switch(direction) {
            case Direction::NORTH:
                if((RoomTile) roomLayout[playerCoords.y-1][playerCoords.x] == RoomTile::FLOOR) playerCoords.y -= 1;
                break;
            case Direction::EAST:
                if((RoomTile) roomLayout[playerCoords.y][playerCoords.x+1] == RoomTile::FLOOR) playerCoords.x += 1;
                break;
            case Direction::SOUTH:
                if((RoomTile) roomLayout[playerCoords.y+1][playerCoords.x] == RoomTile::FLOOR) playerCoords.y += 1;
                break;
            case Direction::WEST:
                if((RoomTile) roomLayout[playerCoords.y][playerCoords.x-1] == RoomTile::FLOOR) playerCoords.x -= 1;
                break;
        }
    }
    
    Coords getMapPosition() {
        return mapPosition;
    }

    Coords getRoomPosition() {
        return roomPosition;
    }
};