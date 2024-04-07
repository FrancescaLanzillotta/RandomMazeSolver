#include <iostream>
#include "Maze.h"

using namespace std;

int main() {
    int size = 10;
    Maze m(size);
    m.initializeMaze();
    cout << m.toString();
    return 0;
}
