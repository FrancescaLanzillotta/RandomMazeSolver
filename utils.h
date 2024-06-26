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
    PATH,
    ERROR,
};

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    STAY,   // Make sure STAY is always the last
};

template<typename T>
static string toString(const vector<T>& v) {
    string s = "[";
    for(int i = 0; i < v.size(); i++){
        s += to_string(v[i]);
        if (i < v.size() - 1)
            s += ", ";
        else
            s += "]";
    }
    return s;
}
#endif //RANDOMMAZE_UTILS_H
