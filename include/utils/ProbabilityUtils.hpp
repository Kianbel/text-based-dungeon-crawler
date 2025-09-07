#pragma once

#include <cmath>
#include <random>

int rollRandomizedRange(int lowestRoll, int highestRoll) {
    int res = lowestRoll + rand() % (highestRoll - lowestRoll + 1);
    return res;
}