#include <iostream>
#include <random>
#include "Maze.h"
using namespace std;

int main() {

    int size = 15;
    random_device rd;  // a seed source for the random number engine
    mt19937 rng(rd()); // mersenne_twister_engine seeded with rd()
    uniform_int_distribution<> distrib(0, size - 1);
    Maze m(size, rng);

    m.generateMaze(false);
    cout << m.toString();

    m.setStart(make_pair(ceil(size/2), ceil(size/2)));
    m.setExit(make_pair(0, 3));
    cout << m.toString();
    return 0;

}
