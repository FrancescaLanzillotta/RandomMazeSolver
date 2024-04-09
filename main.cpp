#include <iostream>
#include <random>
#include "Maze.h"
using namespace std;

bool isExitValid(int r, int c, int size){
    return (((r == 0 || r == size - 1) && c != 0 && c != size - 1) || ((c == 0 || c == size - 1) && r != 0 && r != size - 1));
}
int main() {
    int size = 15;
    Maze m(size);
    m.initializeMaze();

    cout << m.toString();
    delayedCLS(500);

    random_device rd;  // a seed source for the random number engine
    mt19937 rng(rd()); // mersenne_twister_engine seeded with rd()
    uniform_int_distribution<> distrib(0, size - 1);
    int r;
    int c;
    do {
        r = distrib(rng);
        c = distrib(rng);
    } while (!isExitValid(r, c, size));
    r = 3;
    c = 0;
    m.set_exit(r, c);
    cout << m.toString();
    pair<int, int> exit(r, c);
    set<pair<int, int>> visited;
    visited.insert(exit);

    m.generatePath(exit, visited, rng);
    // cout << m.toString();
    return 0;

}
