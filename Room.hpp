#pragma once

#include <ctime>
#include <cstdlib>
#include <iostream>

#include "Utils.hpp"
#include "RoomLayouts.hpp"

enum class RoomSize {
    Small = 0,
    Medium = 1,
    Large = 2,
};

typedef struct {
    int size;
    int variant;
} room;

class Room {
private:
    room r;

public:
    Room() {
        r.size = pickRandomRoomSize();
        r.variant = pickRandomRoomVariant(r.size);
    }

    PAIR_INT generateRoom() {
        return PAIR_INT(r.size, r.variant);
    }

private:
    int pickRandomRoomSize() {
        int chooseSize = rand() % 3;
        switch(chooseSize) {
            case 0:
                return (int) RoomSize::Small;
            case 1:
                return (int) RoomSize::Medium;
            case 2:
                return (int) RoomSize::Large;
        }
        return -1;
    }

    int pickRandomRoomVariant(int roomSize) {
        switch(roomSize) {
            case (int) RoomSize::Small: {
                SmallRoom sr;
                return (rand() %  sr.getVariantsAmount());
            }
            case (int) RoomSize::Medium: {
                MediumRoom mr;
                return (rand() % mr.getVariantsAmount());
            }
            case (int) RoomSize::Large:{
                LargeRoom lr;
                return (rand() % lr.getVariantsAmount());
            }
        }
        return -1;
    }
};