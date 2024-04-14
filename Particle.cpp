//
// Created by franc on 13/04/2024.
//

#include <iostream>
#include "Particle.h"

Particle::Particle(Maze& m) : maze(m){
    setPosition(maze.getStart());

    random_device rd;
    rng = mt19937(rd());
}

const pair<int, int> &Particle::getPosition() const {
    return position;
}

void Particle::setPosition(const pair<int, int> &p) {
    if (maze.areValid(p) && maze.getCell(p) != WALL){
        if (position != make_pair(0, 0)){
            if (maze.getExit() == position)
                maze.setCell(position, EXIT);
            else if(maze.getStart() == position)
                maze.setCell(position, START);
            else
                maze.setCell(position, EMPTY);
        }
        position = p;
        maze.setCell(position, PARTICLE);
    }
}

void Particle::move(Direction d, bool display) {
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
    setPosition(c); // setPosition checks if movement is allowed
    if (display){
        delayedCLS(500);
        cout << maze.toString();
    }
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

bool Particle::isValid(Direction d) {
    bool isValid = false;
    switch (d) {
        case UP:
            isValid = (maze.areValid(position.first - 1, position.second) &&
                        maze.getCell(position.first - 1, position.second) != WALL);
            break;
        case DOWN:
            isValid = maze.areValid(position.first + 1, position.second &&
                        maze.getCell(position.first + 1, position.second) != WALL);
            break;
        case LEFT:
            isValid = maze.areValid(position.first, position.second - 1) &&
                        maze.getCell(position.first, position.second - 1) != WALL;
            break;
        case RIGHT:
            isValid = maze.areValid(position.first, position.second + 1) &&
                        maze.getCell(position.first, position.second + 1) != WALL;
            break;
        case STAY:
            isValid = true;
            break;
    }
    return isValid;
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


