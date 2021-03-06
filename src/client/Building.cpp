#include "Building.h"

#define LENIENCY_FORT 16
#define LENIENCY_FACTORY 8

void Building::markAsSelectedInRange(bool &buildingSelected,
                                     gdouble xStartCoordinate,
                                     gdouble yStartCoordinate,
                                     gdouble xFinishCoordinate,
                                     gdouble yFinishCoordinate) {
    int x = (int) xFinishCoordinate;
    int y = (int) yFinishCoordinate;
    int x_abs = abs(position.first - x);
    int y_abs = abs(position.second - y);

    unsigned int leniency;

    if (buildingType == BuildingsEnum::FORT or
            buildingType == BuildingsEnum::FORT_DESTROYED) {
        /* case building is fort... */
        leniency = LENIENCY_FORT;
    } else {
        /* case building is factory... */
        leniency = LENIENCY_FACTORY;
    }
    if (x_abs <= leniency && y_abs <= leniency) {
        selected = true;
        buildingSelected = true;
    }
}

Building::Building(BuildingsEnum type, int x, int y, int id, TeamEnum team,
                   const std::string& owner, unsigned int hp) :
        buildingType(type),
        position(x, y),
        id(id),
        selected(false),
        team (team),
        owner(owner),
        hp(hp),
        max_hp(hp),
        minutes(0),
        seconds(0)

{
}

unsigned int Building::getXCoordinate() {
    return position.first;
}

unsigned int Building::getYCoordinate() {
    return position.second;
}

BuildingsEnum Building::getBuildingType() {
    return buildingType;
}

TeamEnum Building::getTeam() {
    return team;
}

bool Building::is_selected() {
    return selected;
}

void Building::unselect() {
    selected = false;
}

Building::Building() {
    id = 0;
}

std::string Building::get_owner() {
    return owner;
}

unsigned int Building::get_hp() {
    return hp;
}

unsigned int Building::get_max_hp() {
    return max_hp;
}

int Building::get_ID() {
    return id;
}

void Building::update_time_left(int minutes, int seconds) {
    this->minutes = minutes;
    this->seconds = seconds;
}

void Building::update_hp(unsigned int hp) {
    this->hp = hp;
    if (hp <= 0) {
        destroy();
    }
}

std::pair<int, int> Building::get_time_left() {
    return {minutes, seconds};
}

void Building::destroy() {
    if (buildingType == BuildingsEnum::ROBOT_FABRIC) {
        buildingType = BuildingsEnum::ROBOT_FABRI_DESTROYED;
    } else if (buildingType == BuildingsEnum::VEHICLE_FABRIC) {
        buildingType = BuildingsEnum::VEHICLE_FABRIC_DESTROYED;
    } else if (buildingType == BuildingsEnum::FORT) {
        buildingType = BuildingsEnum ::FORT_DESTROYED;
    }
}

void Building::update_team(TeamEnum team) {
    this->team = team;
}
