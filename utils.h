//
// Created by franc on 06/04/2024.
//

#ifndef RANDOMMAZE_UTILS_H
#define RANDOMMAZE_UTILS_H

#include <thread>
using namespace std;
/**
 * Clears the screen after ms millisencods. Works if the output console emulates the terminal
 * @param ms Number of milliseconds of wait time before the screen is cleared
 */
inline void delayedCLS(int ms=500){
    this_thread::sleep_for(chrono::milliseconds(ms));
    system("cls");
}

enum Cell {
    WALL,
    EMPTY,
    START,
    EXIT,
    DOT,
    ERROR,
};

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    STAY,
};
#endif //RANDOMMAZE_UTILS_H
