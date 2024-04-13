//
// Created by franc on 13/04/2024.
//

#ifndef RANDOMMAZE_PARTICLE_H
#define RANDOMMAZE_PARTICLE_H

#include <utility>
#include "utils.h"
#include "Maze.h"
using namespace std;
class Particle {
private:
    Maze maze;
    pair<int, int> position;
    std::mt19937 rng;

public:
    [[nodiscard]] const pair<int, int> &getPosition() const;

    void setPosition(const pair<int, int> &position);

public:
    Particle(Maze& m, const pair<int, int> &p);
    void move(Direction d);
    void randMove();

};


#endif //RANDOMMAZE_PARTICLE_H
