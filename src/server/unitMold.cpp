//
// Created by rodian on 22/05/17.
//

#include "unitMold.h"

UnitMold::UnitMold(int tec_level, int life, int range, int width, int height,
                     int unit_speed, int fire_rate, int time, std::string type):
tec_level(tec_level), life(life), range(range), width(width), height(height),
unit_speed(unit_speed), fire_rate(fire_rate), creation_time(time), type(type) {}

Unit *UnitMold::createUnit(int x, int y, Map& map) {
    Size unit_size(x,y,width,height);
    Size unit_range(x,y,range,range);
    Unit* new_unit = new Unit(life,type,unit_speed,unit_size,unit_range,map);
    return new_unit;
}

int UnitMold::getTechnologyLevel() const {
    return tec_level;
}

int UnitMold::getCreationTime() {
    return creation_time;
}

std::string UnitMold::getTypeOfUnit() const {
    return type;
}
