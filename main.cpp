#include <iostream>
#include <random>
#include "Maze.h"
#include "Particle.h"
using namespace std;

int main() {

    int size = 25;
    int ms = 150;
    random_device rd;  // a seed source for the random number engine
    mt19937 rng(rd()); // mersenne_twister_engine seeded with rd()
    rng.seed(42);
    Maze m(size, rng);

    m.generateMaze(true);


    vector<Particle> particles;
    int nParticles = 10;
    for (int i = 0; i < nParticles; ++i) {
        particles.emplace_back(m);
        particles[i].setSeed(i + 2);
    }
    bool out = false;
    vector<pair<int, int>> solution;
    while (!out){
        for(auto& p : particles){
            p.randMove(false, 1);

            if (p.getPosition() == m.getExit()){
                out = true;
                solution = p.getPath();
                break;
            }
        }
        delayedCLS(ms);
        cout << m.toString();
    }


    for (auto c : solution){
        m.setCellType(c, PATH);
    }

    while(m.getParticles(m.getExit()) < nParticles){
        for( auto& p : particles){
            if(p.getPosition() != m.getExit()){
                if (m.getCellType(p.getPosition()) != PATH){
                    auto path = p.getPath();
                    p.move(path[path.size() - 2], false);
                } else if (!p.getToExit().empty()){
                    auto ex = p.getToExit();
                    p.move(ex.front(), false);
                    ex.pop_front();
                    p.setToExit(ex);
                } else {
                    int index = 0;
                    for(int i = 0; i < solution.size(); i++){
                        if(p.getPosition() == solution[i]){
                            index = i;
                            break;
                        }
                    }
                    p.setToExit(deque<pair<int, int>>(solution.begin() + index, solution.end()));
                }

                //auto s = p.backtrack(solution, true);
                // p.followPath(s, true);

            }
        }
        delayedCLS(ms);
        cout << m.toString();
    }

    return 0;

}
