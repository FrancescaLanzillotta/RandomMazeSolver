#include <iostream>
#include <random>
#include "Maze.h"
#include "Particle.h"
using namespace std;

int main() {

    int size = 21;
    random_device rd;  // a seed source for the random number engine
    mt19937 rng(rd()); // mersenne_twister_engine seeded with rd()
    uniform_int_distribution<> distrib(0, size - 1);


    Maze m(size, rng);
    m.generateMaze(false);
    cout << m.toString();

    vector<Particle> particles;
    int nParticles = 15;
    for (int i = 0; i < nParticles; ++i) {
        particles.emplace_back(m);

    }
    bool out = false;
    while (!out){
        for(auto& p : particles){
            p.randMove(false);
            delayedCLS(1);
            cout << m.toString();
            if (p.getPosition() == m.getExit()){
                out = true;
                break;
            }
        }
    }
    return 0;

}
