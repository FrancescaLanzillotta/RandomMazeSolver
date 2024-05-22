//
// Created by franc on 13/04/2024.
//

#include <iostream>
#include "Particle.h"

Particle::Particle(Maze& m) : maze(m){
    setPosition(maze.getStart());
    path.push_back(position);
    random_device rd;
    rng = mt19937(rd());
    prevMove = STAY;
}

const pair<int, int> &Particle::getPosition() const {
    return position;
}

void Particle::setPosition(const pair<int, int> &p) {
    if (maze.areValid(p) && maze.getCellType(p) != WALL){
        if (position != make_pair(0, 0))   // position not initialized yet
            maze.removeParticle(position);
        position = p;
        maze.addParticle(position);
    }
}

pair<int, int> Particle::toCoordinates(Direction d) {
    pair<int, int> c;
    switch (d) {
        case UP:
            c = make_pair(position.first - 1, position.second);
            break;
        case DOWN:
            c = make_pair(position.first + 1, position.second);
            break;
        case LEFT:
            c = make_pair(position.first, position.second - 1);
            break;
        case RIGHT:
            c = make_pair(position.first, position.second + 1);
            break;
        case STAY:
            c = position;
            break;
    }
    return c;
}
Direction Particle::toDirection(pair<int, int> c) {
    Direction d;
    if (c == make_pair(position.first - 1, position.second))
        d = UP;
    else if (c == make_pair(position.first + 1, position.second))
        d = DOWN;
    else if (c == make_pair(position.first, position.second - 1))
        d = LEFT;
    else if (c == make_pair(position.first, position.second + 1))
        d = RIGHT;
    else
        d = STAY;
    return d;
}


bool Particle::isValid(Direction d) {
    pair<int, int> c = toCoordinates(d);
    return maze.areValid(c) && maze.getCellType(c) != WALL;
}

void Particle::move(pair<int, int> c, bool display) {
    setPosition(c); // setPosition checks if movement is allowed

    if (path.size() > 1 && position == path[path.size() - 2]) // backtracking
        path.pop_back();
    else
        path.push_back(position); // moving forward
    if (position == maze.getExit())
        maze.removeParticle(maze.getExit());
    if (display){
        delayedCLS(100);
        cout << maze.toString();
    }
}


void Particle::move(Direction d, bool display) {
    move(toCoordinates(d), display);
}

/***
 * This function picks a random move out of the ones available to the particle, with the option to inhibit the choice of
 * going backward with a certain probability. This makes the particle move less erraticly, pushing it to move further
 * through the labyrinth, instead of goig back and forth.
 * removeBackProb = 1 removes the move every time thare is more than one choice available, that is the particle is not
 * ina a dead end.
 * removeBackProb = 0 never removes the backward move, that is the particle moves truly randomly.
 * @param display Whether to display the maze or not
 * @param removeBackProb Probability of removing the backward move if there is more than one choice available.
 *
 */
void Particle::randMove(bool display, float removeBackProb = 0) {
    Direction backward;
    switch (prevMove) {
        case UP:
            backward = DOWN;
            break;
        case DOWN:
            backward = UP;
            break;
        case LEFT:
            backward = RIGHT;
            break;
        case RIGHT:
            backward = LEFT;
            break;
        case STAY:
            backward = STAY;
            break;
    }

    vector<Direction> moves;                // find all availbles moves
    for (int d = 0; d != STAY; d++) {
        auto dir = static_cast<Direction>(d);
        if (isValid(dir))
            moves.push_back(static_cast<Direction>(d));
    }

    Direction next;
    if (moves.size() > 1){
        for( int i = 0; i < moves.size(); i++){
            if (moves[i] == backward){
                std::bernoulli_distribution b(removeBackProb);
                if (b(rng) == 1){   // remove the backward move with specified probability
                    moves.erase(moves.begin() + i);
                }
            }
        }
        uniform_int_distribution<> dir(0, moves.size() - 1);
        next = moves[dir(rng)];     // random choice out of the elements in moves

    } else      // nothing to choose
        next = moves[0];

    prevMove = next;
    move(next, display);
}

const vector<pair<int, int>> &Particle::getPath() const {
    return path;
}

vector<pair<int, int>> Particle::backtrack(const vector<pair<int, int>>& solution, bool display) {
    while (maze.getCellType(position) != PATH){
        move(path[path.size() - 2], display); // backtracking
    }
    int index = 0;
    for(int i = 0; i < solution.size(); i++){
        if(position == solution[i]){
            index = i;
            break;
        }
    }
    return vector<pair<int, int>> (solution.begin() + index, solution.end());
}

void Particle::followPath(const vector<pair<int, int>> &p, bool display) {
    for (auto c : p){
        move(c, display);
        // maze.setCellType(path[path.size() - 2], PATH);
    }
}

void Particle::setSeed(int seed) {
    rng.seed(seed);
}









