#pragma once

#include <ctime>
#include <cstdlib>
#include <iostream>

#include "../utils/Utils.hpp"
#include "RoomLayouts.hpp"

enum class RoomSize {
    Small = 0,
    Medium = 1,
    Large = 2,
};

class Room {
private:
    int size;
    int variant;
    VECTOR2D roomData;

public:
    Room() {
        size = pickRandomRoomSize();
        variant = pickRandomRoomVariant(size);
        roomData = generate(size, variant);
    }

    VECTOR2D getRoomData() {
        return roomData;
    }


private:
    VECTOR2D generate(int size, int variant) {
        switch(size) {
            case (int) RoomSize::Small: {
                SmallRoom sr;
                return sr.getVariantData(variant);
            }
            case (int) RoomSize::Medium: {
                MediumRoom mr;
                return mr.getVariantData(variant);
            }
            case (int) RoomSize::Large:{
                LargeRoom lr;
                return lr.getVariantData(variant);
            }
        }
        SmallRoom sr;
        return sr.getVariantData(variant);
    }


    int pickRandomRoomSize() {
        int chooseSize = rollRandomizedRange(0,0);
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

    int pickRandomRoomVariant(int size) {
        switch(size) {
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