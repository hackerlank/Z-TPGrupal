#ifndef Z_TPGRUPAL_UNITSMONITOR_H
#define Z_TPGRUPAL_UNITSMONITOR_H


#include <mutex>
#include "Unit.h"

class UnitsMonitor {
    std::vector<Unit> &units;
    std::mutex m;

public:
    explicit UnitsMonitor(std::vector<Unit> &units);

    void addUnit(Unit &unit);

    void removeUnit(int id);

    void update_position(int unit_id, int x, int y);

    std::vector<Unit>
    getUnitsToDraw(unsigned int minX, unsigned int maxX, unsigned int minY,
                   unsigned int maxY);

    void
    markAsSelectedInRange(bool &unitsSelected, gdouble xStartCoordinate,
                          gdouble yStartCoordinate, gdouble xFinishCoordinate,
                          gdouble yFinishCoordinate);

    void wipeSelected();

    std::vector<Unit> getSelectedUnits();
};


#endif //Z_TPGRUPAL_UNITSMONITOR_H
