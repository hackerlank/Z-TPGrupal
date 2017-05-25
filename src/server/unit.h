//
// Created by rodian on 18/05/17.
//

#ifndef Z_TPGRUPAL_UNIT_H
#define Z_TPGRUPAL_UNIT_H

#include "Occupant.h"
#include "compass.h"
#include "teamable.h"
//#include "map.h"

class Map;

class Unit: public Occupant, public Teamable {
private:
    Compass compass;
    int unit_speed;
    // State of Unit can be "atk" if is attacking, "mv" if is moving, "std" if
    // is standing still
    std::string state;
    Size range;
    Map map;
    std::vector<Position>* road;

public:
    Unit(int life, std::string type, int unit_speed, Size size, Size range,
                                                                Map& map);

    // Calculates the minimum road to destiny (x,y)
    void calculateRoadTo(int x, int y);

    // Indicates the Unit to make the next step on the road.
    // Make sure of use the calculateRoadTo method before this one.
    void move();

    // Returns the current position of the unit
    Position getCurrentPosition() const;

    // Returns "atk" if is attacking, "mv" if is moving, "std" if
    // is standing still
    std::string getState() const;

    void grab(Teamable* object, std::string type);

    //void attack(Occupable)-> make check is i have explosive attack for buildings
};


#endif //Z_TPGRUPAL_UNIT_H