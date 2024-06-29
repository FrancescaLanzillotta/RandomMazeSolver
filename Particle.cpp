//
// Created by franc on 13/04/2024.
//

#include <iostream>
#include <utility>
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

/***
 * This function sets the new position of the particle in the maze. To do that, it checks if the coordinates are valid,
 * if the new cell isn't a wall and updates the number of particles in both the old and new cells in the maze.
 * @param p pair of coordinates to set the position to
 */
void Particle::setPosition(const pair<int, int> &p) {
    if (maze.areValid(p) && maze.getCellType(p) != WALL){
        if (position != make_pair(0, 0))   // position not initialized yet
            maze.removeParticle(position);
        position = p;
        maze.addParticle(position);
    }
}

/***
 * This functions converts a given Direction to a pair of coordinates
 * @param d direction to convert
 * @return pair of coordinates corresponding to the position of the particle moved in direction d
 */
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

/***
 * This functions moves the particle in the specified coordinates. The function adds the new coordinates to particle's
 * path if the particle is not backtracking. Moreover, if the particle reaches the exit, it's removed from the maze.
 * @param c new coordinates to move the particle to
 * @param ms whether to display the maze
 */
void Particle::move(pair<int, int> c, int ms) {
    setPosition(c); // setPosition checks if movement is allowed

    if (path.size() > 1 && position == path[path.size() - 2]) // backtracking
        path.pop_back();
    else
        path.push_back(position); // moving forward
    if (ms > 0){
        delayedCLS(ms);
        cout << maze.toString();
    }
}


void Particle::move(Direction d, int ms) {
    move(toCoordinates(d), ms);
}

/***
 * This function picks a random move out of the ones available to the particle, with the option to inhibit the choice of
 * going backward with a certain probability. This makes the particle move less erraticly, pushing it to move further
 * through the labyrinth, instead of goig back and forth.
 * removeBackProb = 1 removes the move every time thare is more than one choice available, that is the particle is not
 * ina a dead end.
 * removeBackProb = 0 never removes the backward move, that is the particle moves truly randomly.
 * @param ms whether to display the maze or not
 * @param removeBackProb probability of removing the backward move if there is more than one choice available.
 *
 */
void Particle::randMove(int ms, float removeBackProb = 0) {
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
    move(next, ms);
}

const vector<pair<int, int>> &Particle::getPath() const {
    return path;
}

/***
 * This function backtracks the particle along its path until it reaches a cell in the solution's path. It's guaranteed
 * that such cell exists, since all cells have the same starting point.
 * @param solution vector containing the solution's path
 * @param ms whether to diplay the maze or not
 * @return tha path towards the exit starting from the cell on the solution's path
 */
vector<pair<int, int>> Particle::backtrack(const vector<pair<int, int>>& solution, int ms) {
    while (maze.getCellType(position) != PATH){
        move(path[path.size() - 2], ms); // backtracking
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

void Particle::followPath(const vector<pair<int, int>> &p, int ms) {
    for (auto c : p){
        move(c, ms);
    }
}

deque<pair<int, int>> &Particle::getToExit()  {
    return toExit;
}

void Particle::setToExit(deque<pair<int, int>> toExit) {
    Particle::toExit = std::move(toExit);
}









