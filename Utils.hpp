#pragma once

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
} Coords;

enum class Direction {
    NORTH,
    EAST,
    SOUTH,
    WEST
};

typedef std::vector<std::vector<int>> VECTOR2D; 
typedef std::string STRING;
typedef std::pair<int,int> PAIR_INT;
