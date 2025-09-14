#pragma once

#include <vector>
#include <string>

enum class MapTile {
    EMPTY = 0,
    CENTER_ROOM = 1,
    VERTICAL_CORRIDOR = 2,
    HORIZONTAL_CORRIDOR = 3,
    NORMAL_ROOM = 4
};

enum class RoomTile {
    EMPTY = -1,
    FLOOR = 0,
    WALL = 1,
    DOOR = 2,
};

struct Coords {
    int x;
    int y;
};

enum class Direction {
    NORTH,
    EAST,
    SOUTH,
    WEST
};

typedef std::vector<std::vector<int>> VECTOR2D; 
typedef std::string STRING;
typedef std::pair<int,int> PAIR_INT;
