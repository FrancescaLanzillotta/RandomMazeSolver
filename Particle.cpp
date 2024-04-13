//
// Created by franc on 13/04/2024.
//

#include "Particle.h"

Particle::Particle(const pair<int, int> &position) : position(position) {}

const pair<int, int> &Particle::getPosition() const {
    return position;
}

void Particle::setPosition(const pair<int, int> &position) {
    Particle::position = position;
}
