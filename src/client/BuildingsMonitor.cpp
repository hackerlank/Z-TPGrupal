#include "BuildingsMonitor.h"
#include <Lock.h>


void BuildingsMonitor::markAsSelectedInRange(bool &buildingSelected,
                                             gdouble xStartCoordinate,
                                             gdouble yStartCoordinate,
                                             gdouble xFinishCoordinate,
                                             gdouble yFinishCoordinate) {
    Lock l(m);
    for (Building &building : buildings) {
        /* each player has to selects its units in range */
        building.markAsSelectedInRange(buildingSelected, xStartCoordinate,
                                       yStartCoordinate, xFinishCoordinate,
                                       yFinishCoordinate);
        if (buildingSelected) {
            break;
        }
    }
}

void BuildingsMonitor::addBuilding(Building &b) {
    Lock l(m);
    buildings.push_back(b);
}

std::vector<Building>
BuildingsMonitor::getBuildingsToDraw(unsigned int minX, unsigned int maxX,
                                     unsigned int minY, unsigned int maxY) {
    Lock l(m);
    std::vector<Building> returnVector;

    for (Building &building : buildings) {
        if (building.getXCoordinate() >= minX and
            building.getXCoordinate() <= maxX and
            building.getYCoordinate() >= minY and
            building.getYCoordinate() <= maxY) {
            returnVector.emplace_back(building);
        }
    }
    return returnVector;
}

std::vector<Building> BuildingsMonitor::get_selected() {
    std::vector<Building> selected_buildings;
    for (Building &building : buildings) {
        if (building.is_selected()) {
            selected_buildings.push_back(building);
        }
    }
    return selected_buildings;
}

void BuildingsMonitor::wipe_selected() {
    for (Building &b: buildings) {
        b.unselect();
    }
}

Building BuildingsMonitor::get_building(int id) {
    Lock l(m);
    for (Building& building: buildings) {
        if (building.get_ID() == id) {
            return building;
        }
    }
    return Building();
}

void
BuildingsMonitor::update_building(int id, int minutes, int seconds, int hp,
                                  TeamEnum team) {
    Lock l(m);
    for (auto b = buildings.begin(); b != buildings.end(); ++b) {
        if (b->get_ID() == id) {
            b->update_hp(hp);
            b->update_time_left(minutes, seconds);
            b->update_team(team);
        }
    }
}

void BuildingsMonitor::clear() {
    Lock l(m);
    buildings.clear();
}
