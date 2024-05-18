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
    std::mt19937 rng;

public:
    [[nodiscard]] const pair<int, int> &getPosition() const;
    void setPosition(const pair<int, int> &position);
    [[nodiscard]] const vector<pair<int, int>> &getPath() const;
    explicit Particle(Maze& m);
    void setSeed(int seed);
    pair<int, int> toCoordinates(Direction d);
    Direction toDirection(pair<int, int> c);
    bool isValid(Direction d);
    void move(pair<int, int> c, bool display);
    void move(Direction d, bool display);
    void randMove(bool display = false);
    vector<pair<int, int>> backtrack(const vector<pair<int, int>>& solution, bool display);
    void followPath(const vector<pair<int, int>>& p, bool display);
};


#endif //RANDOMMAZE_PARTICLE_H
