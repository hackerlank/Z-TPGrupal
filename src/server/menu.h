//
// Created by rodian on 29/05/17.
//

#ifndef Z_TPGRUPAL_MENU_H
#define Z_TPGRUPAL_MENU_H


#include <vector>
#include <iostream>
#include <mutex>
#include "player.h"
class Player;
class Lobby;

class Menu {
private:
    std::vector<Player*> players;
    std::mutex m;
    int lobby_counter;
    std::vector<Lobby*> lobbies;
    std::string& config;
public:
    Menu(std::string& config);

    bool addPlayer(Messenger* msgr, Menu& menu, std::string player_id);

    void createNewLobby(Player* player);

    std::string getLobbiesInfo();

    std::string changeName(std::string &new_name);

    bool addToLobby(int id_lobby, Player *player);

    void shutDown();

    void disconectPlayer( Player *player);

    ~Menu();
};


#endif //Z_TPGRUPAL_MENU_H
