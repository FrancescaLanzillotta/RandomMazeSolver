//
// Created by franc on 13/04/2024.
//

#ifndef RANDOMMAZE_PARTICLE_H
#define RANDOMMAZE_PARTICLE_H

#include <utility>
#include <deque>
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
    deque<pair<int, int>> toExit;
public:
    explicit Particle(Maze& m);
    deque<pair<int, int>> &getToExit();
    void setToExit(deque<pair<int, int>> toExit);
    [[nodiscard]] const pair<int, int> &getPosition() const;
    void setPosition(const pair<int, int> &position);
    [[nodiscard]] const vector<pair<int, int>> &getPath() const;
    pair<int, int> toCoordinates(Direction d);
    Direction toDirection(pair<int, int> c);
    bool isValid(Direction d);
    void randMove(int ms, float removeBackProb);
    vector<pair<int, int>> backtrack(const vector<pair<int, int>>& solution, int ms);
    void followPath(const vector<pair<int, int>>& p, int ms);
    void move(pair<int, int> c, int ms);
    void move(Direction d, int ms);

};


#endif //RANDOMMAZE_PARTICLE_H
