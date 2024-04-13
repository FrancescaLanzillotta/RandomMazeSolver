#include <iostream>
#include <random>
#include "Maze.h"
#include "Particle.h"
using namespace std;

int main() {

    int size = 15;
    random_device rd;  // a seed source for the random number engine
    mt19937 rng(rd()); // mersenne_twister_engine seeded with rd()
    uniform_int_distribution<> distrib(0, size - 1);




    Maze m(size, rng);
    m.generateMaze(false);
    cout << m.toString();
    Particle p(m);

    while (p.getPosition() != m.getExit()){
        p.randMove();
        delayedCLS(1);
        cout << m.toString();
    }









    /*
    uniform_int_distribution<> dir(0, 4);
    for (int i = 0; i < 5; ++i) {
        auto d = static_cast<Direction>(dir(rng));
        switch (d) {
            case UP:
                cout << "UP" << endl;
                break;
            case DOWN:
                cout << "DOWN" << endl;
                break;
            case LEFT:
                cout << "LEFT" << endl;
                break;
            case RIGHT:
                cout << "RIGHT" << endl;
                break;
            case STAY:
                cout << "STAY" << endl;
                break;
        }
    }
    */
    return 0;

}
