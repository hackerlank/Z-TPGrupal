#ifndef Z_TPGRUPAL_GAMEBUILDER_H
#define Z_TPGRUPAL_GAMEBUILDER_H

#include <gtkmm.h>
#include <string>

#include "windows/GameWindow.h"
#include "BuildingsMonitor.h"
#include "MapMonitor.h"
#include "ServerMessenger.h"
#include "windows/InitialWindow.h"
#include "windows/LobbyWindow.h"
#include "windows/MenuWindow.h"
#include "windows/ResultWindow.h"

class GameBuilder {
    InitialWindow *init_window;
    MenuWindow* menu_window;
    LobbyWindow* lobby_window;
    GameWindow *window;
    ResultWindow* result_window;
    Glib::RefPtr<Gtk::Builder> refBuilder;

public:
    GameBuilder();
    ~GameBuilder();

    // returns the generated window
    GameWindow *get_window();

    InitialWindow *get_initial_window();
    LobbyWindow* get_lobby_window();
    MenuWindow* get_menu_window();
    ResultWindow* get_result_window();

private:
    void start();
    void clean();
};


#endif //Z_TPGRUPAL_GAMEWINDOW_H
