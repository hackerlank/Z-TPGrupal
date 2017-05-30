//
// Created by rodian on 22/05/17.
//

#ifndef Z_TPGRUPAL_CONTROUNIT_H
#define Z_TPGRUPAL_CONTROUNIT_H

#include <iostream>
#include <chrono>
#include <thread>
#include "unit.h"
#include "../Lock.h"
#include "command.h"
#include "../messenger.h"

class Command;

class ControlUnit {
private:
    std::vector<Unit*> all_units;
    std::vector<Occupant*> all_occupants;
    std::vector<Messenger*> players;
    std::vector<Command>* commands;
    std::mutex m;
    bool winning;

public:
    ControlUnit(std::vector<Messenger*>& new_players);

    // Method to start checking commands from players
    void run();

    void sleepFor(double sec);

    // Meant to make every unit make a micro action on the Tic
    void unitsMakeMicroAcction();

    // Checks if any Occupant is dead. If so, it will remove it from the game
    void checkAllLivingOccupants();

    // Command move unit. Meant to give the order to the unit to start moving
    // to de (x,y) position
    void cmdMoveUnit(int id, int x, int y);

private:
    // Process all commands on commands vector and leaves the vector empty
    void executeCommands();

    void sendUpdateMessage();

    std::string getUpdateInfo();
};


#endif //Z_TPGRUPAL_CONTROUNIT_H
