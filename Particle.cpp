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
}

const pair<int, int> &Particle::getPosition() const {
    return position;
}

void Particle::setPosition(const pair<int, int> &p) {
    if (maze.areValid(p) && maze.getCellType(p) != WALL){
        if (position != make_pair(0, 0)){   // position not initialized yet
            maze.removeParticle(position);
            /*
            if (maze.getExit() == position)
                maze.setCell(position, EXIT, maze.getParticles(position) - 1);
                // maze.setCellType(position, EXIT);
            else if(maze.getStart() == position)
                maze.setCellType(position, START);
            else
                maze.setCellType(position, EMPTY);
                */

        }

        position = p;
        maze.addParticle(position);
        //maze.setCellType(position, PARTICLE);
    }
}
/*
void Particle::setPosition(const pair<int, int> &p, Cell underneath){
    if (maze.areValid(p) && maze.getCellType(p) != WALL){
        if (position != make_pair(0, 0)){   // position not initialized yet
            if (maze.getExit() == position)
                maze.setCellType(position, EXIT);
            else if(maze.getStart() == position)
                maze.setCellType(position, START);
            else
                maze.setCellType(position, underneath);
        }

        position = p;
        maze.setCellType(position, PARTICLE);
    }
}
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
    if (display){
        delayedCLS(500);
        cout << maze.toString();
    }
}


void Particle::move(Direction d, bool display) {
    move(toCoordinates(d), display);
}

void Particle::randMove(bool display) {
    vector<Direction> moves;
    for (int d = 0; d != STAY; d++) {
        if (isValid(static_cast<Direction>(d)))
            moves.push_back(static_cast<Direction>(d));
    }
    uniform_int_distribution<> dir(0, moves.size() - 1);
    move(moves[dir(rng)], display);
}

const vector<pair<int, int>> &Particle::getPath() const {
    return path;
}

vector<pair<int, int>> Particle::backtrack(const vector<pair<int, int>>& solution, bool display) {
    bool onTrack = false;
    int index;
    while (!onTrack){
        for(int i = 0; i < solution.size(); i++){
            if(position == solution[i]){
                onTrack = true;
                index = i;
                break;
            } else {
                // path.pop_back();
                auto cell = path[path.size() - 2];
                move(cell, display);
                /*
                if (maze.getCellType(cell) == PARTICLE)
                    move(cell, PARTICLE, display);
                else
                    move(cell, EMPTY, display);
                    */
            }
        }
    }
    return vector<pair<int, int>> (solution.begin() + index, solution.end());
}

void Particle::followPath(const vector<pair<int, int>> &p, bool display) {
    for (auto c : p){
        move(c, display);
        maze.setCellType(path[path.size() - 2], PATH);
    }
}

void Particle::setSeed(int seed) {
    rng.seed(seed);
}








