//
// Created by franc on 13/04/2024.
//

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
    if (maze.areValid(p)){
        position = p;
        maze.setCell(position, PARTICLE);
    }
}

void Particle::move(Direction d) {
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

    if (maze.getCell(c) == EMPTY){
        setPosition(c);    // setCell checks if coordinates are valid
    }

}

void Particle::randMove() {
    uniform_int_distribution<> dir(0, 4);
    move(static_cast<Direction>(dir(rng)));
}


