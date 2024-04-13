//
// Created by franc on 13/04/2024.
//

#include "Particle.h"

Particle::Particle(Maze& m, const pair<int, int> &p) : maze(m), position(p) {
    random_device rd;
    rng = mt19937(rd());
}

const pair<int, int> &Particle::getPosition() const {
    return position;
}

void Particle::setPosition(const pair<int, int> &p) {
    Particle::position = p;
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
        position = c;
        maze.setCell(c, PARTICLE);     // setCell checks if coordinates are valid
    }

}

void Particle::randMove() {
    uniform_int_distribution<> dir(0, 4);
    move(static_cast<Direction>(dir(rng)));
}


