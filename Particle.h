//
// Created by franc on 13/04/2024.
//

#ifndef RANDOMMAZE_PARTICLE_H
#define RANDOMMAZE_PARTICLE_H

#include <utility>

using namespace std;
class Particle {
private:
    pair<int, int> position;
public:
    [[nodiscard]] const pair<int, int> &getPosition() const;

    void setPosition(const pair<int, int> &position);

public:
    explicit Particle(const pair<int, int> &position);
};


#endif //RANDOMMAZE_PARTICLE_H
