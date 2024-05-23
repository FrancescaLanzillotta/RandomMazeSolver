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
    Direction prevMove;
public:
    explicit Particle(Maze& m);
    [[nodiscard]] const pair<int, int> &getPosition() const;
    void setPosition(const pair<int, int> &position);
    [[nodiscard]] const vector<pair<int, int>> &getPath() const;
    void setSeed(int seed);
    pair<int, int> toCoordinates(Direction d);
    Direction toDirection(pair<int, int> c);
    bool isValid(Direction d);
    void randMove(bool display, float removeBackProb);
    vector<pair<int, int>> backtrack(const vector<pair<int, int>>& solution, bool display);
    void followPath(const vector<pair<int, int>>& p, bool display);
private:
    void move(pair<int, int> c, bool display);
    void move(Direction d, bool display);

};


#endif //RANDOMMAZE_PARTICLE_H
