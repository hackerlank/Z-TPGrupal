#ifndef Z_TPGRUPAL_CLIENTTREAD_H
#define Z_TPGRUPAL_CLIENTTREAD_H


#include "PlayersMonitor.h"
#include "BuildingsMonitor.h"
#include "MapMonitor.h"
#include "../Thread.h"

class ClientThread : public Thread {
public:
    ClientThread(PlayersMonitor &playerMonitor,
                     BuildingsMonitor &buildingsMonitor,
                     MapMonitor &mapMonitor);

    virtual void run();

private:
    PlayersMonitor &playersMonitor;

    BuildingsMonitor &buildingsMonitor;

    MapMonitor &mapMonitor;
};


#endif //Z_TPGRUPAL_CLIENTTREAD_H
