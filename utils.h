//
// Created by franc on 06/04/2024.
//

#ifndef RANDOMMAZE_UTILS_H
#define RANDOMMAZE_UTILS_H

#include <thread>
using namespace std;

void delayedCLS(int ms){
    this_thread::sleep_for(chrono::milliseconds(ms));
    system("cls");
}
#endif //RANDOMMAZE_UTILS_H
