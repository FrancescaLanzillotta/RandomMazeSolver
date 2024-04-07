#include <iostream>
#include "Maze.h"
#include "utils.h"
using namespace std;

int main() {
    // delayedCLS(1);
    int size = 11;
    Maze m(size);
    m.initializeMaze();
    cout << m.toString();
    delayedCLS(1000);
    m.set_exit(1, size - 1);
    cout << m.toString();
    return 0;
}
