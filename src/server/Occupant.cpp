//
// Created by rodian on 13/05/17.
//

#include "Occupant.h"

Occupant::Occupant(int id, int life, std::string type, Size position) :
       Teamable(position), id(id), life_points(life), type(type)/*,
       occ_size(position)*/, damage_recv(0) {}

Occupant::Occupant() :
        Teamable(Size(3,3,3,3)), id(-1), life_points(0), type("nullOccupant")/*,
       occ_size(position)*/, damage_recv(0) {}

std::string Occupant::getType() const {
    return this->type;
}

void Occupant::reduceLifeBy(int dmg) {
    this->damage_recv += dmg;
    this->changed = true;
}

bool Occupant::areYouAlive() {
    return ((life_points - damage_recv) > 0);
}

//bool Occupant::isThereACollision(Size &other) {
//    return occ_size.isThereACollision(other);
//}

int Occupant::getLifeLeft() {
    return life_points - damage_recv;
}

Occupant::~Occupant() {}

int Occupant::getId() {
    return id;
}


