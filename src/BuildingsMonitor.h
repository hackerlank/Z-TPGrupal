#ifndef Z_TPGRUPAL_BUILDINGSMONITOR_H
#define Z_TPGRUPAL_BUILDINGSMONITOR_H


#include <mutex>
#include "Building.h"

class BuildingsMonitor {
private:
    std::vector<Building> &buildings;

    std::mutex m;
public:
    BuildingsMonitor(std::vector<Building> &buildings);
};


#endif //Z_TPGRUPAL_BUILDINGSMONITOR_H
