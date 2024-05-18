#include <iostream>
#include <random>
#include "Maze.h"
#include "Particle.h"
using namespace std;

int main() {

    int size = 21;
    random_device rd;  // a seed source for the random number engine
    mt19937 rng(rd()); // mersenne_twister_engine seeded with rd()
    rng.seed(42);
    Maze m(size, rng);

    m.generateMaze(true);


    vector<Particle> particles;
    int nParticles = 5;
    for (int i = 0; i < nParticles; ++i) {
        particles.emplace_back(m);
        particles[i].setSeed(i + 2);
    }
    bool out = false;
    vector<pair<int, int>> solution;
    while (!out){
        for(auto& p : particles){
            p.randMove(false, 2);
            delayedCLS(1);
            cout << m.toString();
            if (p.getPosition() == m.getExit()){
                out = true;
                solution = p.getPath();
                break;
            }
        }
    }

//    for(auto c : solution){
//        printf("[%d, %d]\n   |\n   v\n", c.first, c.second);
//    }

    for (auto c : solution){
        m.setCellType(c, PATH);
    }

    for( auto& p : particles){
        if(p.getPosition() != m.getExit()){
            auto s = p.backtrack(solution, true);
            p.followPath(s, true);

        }
    }

    /*
    Particle p(m);
    vector<Direction> path;
    vector<Direction> moveset = {UP, UP, UP, UP, LEFT, LEFT};

    for (auto move : moveset){
        p.move(move, false);
        m.setCellType(p.getPath()[p.getPath().size() - 2], PATH);
        delayedCLS(1000);
        cout << m.toString();
        path.push_back(move);
    }

    while (!path.empty()){
        Direction pathMove = path.back();
        path.pop_back();
        Direction backtrack;
        switch (pathMove) {
            case UP:
                backtrack = DOWN;
                break;
            case DOWN:
                backtrack = UP;
                break;
            case LEFT:
                backtrack = RIGHT;
                break;
            case RIGHT:
                backtrack = LEFT;
                break;
            case STAY:
                backtrack = STAY;
                break;
        }
        p.move(backtrack, false);
        delayedCLS(1000);
        cout << m.toString();
    }


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

    */
    return 0;

}
