//
// Created by rodian on 22/05/17.
//

#include "factory.h"

Factory::Factory(int life, std::string type, Size position,
                           std::vector<UnitMold> units) :
Occupant(life,type, position), Teamable(position), running(false), units(units){
    it = units.begin();
}

void Factory::build() {
    this->running = true;

    while (running) {
        // after sleeping time expected
        // create the correct amount of units
        // units. setTeam(this->team);
    }
}

void Factory::stopBuilding() {
    this->running = false;
}

int Factory::getSelectedUnitTime() {
    return it->getCreationTime();
}

std::string Factory::nextUnit() {
    int i = 0;
    while (i == 0 || it->getTechnologyLevel() > this->tech_level) {
        ++it;
        if (it == units.end())
            it = units.begin();
        ++i;
    }
    return it->getTypeOfUnit();
}

Occupant *Factory::destroyFactory() {
    // capaz necesite un tipo distinto a Occupant para que no pueda ser
    // destruido ni atacado
    Occupant* ruins = new Occupant(1000,"Ruins",this->occ_size);
    return ruins;
}

void Factory::setNewPlayer(std::string player, int tech_level) {
    this->tech_level = tech_level;
    this->team = player;
}