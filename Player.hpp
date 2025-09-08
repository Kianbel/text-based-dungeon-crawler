#pragma once

#include "Map.hpp"
#include "Utils.hpp"

class Player {
private:
    VECTOR2D mapData;
    Coords pos;
    int health;
    int armor;

public:
    Player(VECTOR2D& mapData, int mapDimension) {
        this->mapData = mapData;
        this->pos = {mapDimension/2 , mapDimension/2};
        health = 100;
        armor = 0;
    }

    void move(Direction direction) {
        std::cout << "\nPlayer x,y: {" << pos.x << "," << pos.y << "}\n";

        switch((int) direction) {
            case (int) Direction::NORTH:
                if(mapData[pos.y-1][pos.x] == (int) RoomTileType::NORTH_CORRIDOR) {
                    pos.y -= 2;
                }
                else {
                    std::cout << "Player can't go north, something's blocking the way.\n";
                }
                break;
            case (int) Direction::EAST:
                if(mapData[pos.y][pos.x+1] == (int) RoomTileType::EAST_CORRIDOR) {
                    pos.x += 2;
                }
                else {
                    std::cout << "Player can't go east, something's blocking the way.\n";
                }
                break;
            case (int) Direction::SOUTH:
                if(mapData[pos.y+1][pos.x] == (int) RoomTileType::SOUTH_CORRIDOR) {
                    pos.y += 2;
                }
                else {
                    std::cout << "Player can't go south, something's blocking the way.\n";
                }
                break;
            case (int) Direction::WEST:
                if(mapData[pos.y][pos.x-1] == (int) RoomTileType::WEST_CORRIDOR) {
                    pos.x -= 2;
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

    Coords getPosition() {
        return pos;
    }
};