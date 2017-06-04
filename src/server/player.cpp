//
// Created by rodian on 29/05/17.
//

#include "player.h"

Player::Player(std::string id, Messenger *msg, ControlUnit* control, Menu& menu) :
        id(id), messenger(msg), conected(true),on_menu(true),on_lobby(false),
        playing(false), control(control), menu(menu) {}

Player::Player(std::string id, Messenger *msg, Menu& menu) :
        id(id), messenger(msg), conected(true),on_menu(true),on_lobby(false),
        playing(false),menu(menu) {}

void Player::run() {
    while (conected) {
        std::string new_cmd = messenger->recieveMessage();

        if (on_menu) {
            processMenuCommands(new_cmd);
        }else if (on_lobby) {
            processLobbyCommands(new_cmd);
        } else if (playing) {
            cmds.push_back(new Command(new_cmd,control));
        }
    }
}

void Player::updateInfo(std::string &info) {
    messenger->sendMessage(info);
}

void Player::addControlUnit(ControlUnit *control) {
    this->control = control;
}

Messenger *Player::getMessenger() {
    return messenger;
}

void Player::addLobby(Lobby* lobby) {
    this->lobby = lobby;
    on_lobby = true;
}

void Player::processMenuCommands(std::string &cmd) {
    if (cmd == "create lobby") {
        this->menu.createNewLobby(this);
        on_menu = false;
    }
}

void Player::processLobbyCommands(std::string &cmd) {
    if (cmd == "start game") {
        this->lobby->startGame();
        on_lobby = false;
    }
}
