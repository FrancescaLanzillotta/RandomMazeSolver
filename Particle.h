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
    Maze& maze;
    pair<int, int> position;
    vector<pair<int, int>> path;
private:
    std::mt19937 rng;

public:
    [[nodiscard]] const pair<int, int> &getPosition() const;
    void setPosition(const pair<int, int> &position);
    const vector<pair<int, int>> &getPath() const;
    explicit Particle(Maze& m);
    pair<int, int> toCoordinates(Direction d);
    bool isValid(Direction d);
    void move(pair<int, int> c, bool display);
    void move(Direction d, bool display);
    void randMove(bool display = false);

};


#endif //RANDOMMAZE_PARTICLE_H
