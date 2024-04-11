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

    cout << m.toString();
    delayedCLS(5000);



    set<pair<int, int>> visited;

    m.generatePath(m.getExit(), visited);

    return 0;

}
