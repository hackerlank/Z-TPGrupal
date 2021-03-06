#include <gtkmm.h>
#include <iostream>
#include "ClientThread.h"
#include "GameBuilder.h"
#include "Game.h"
#include <split.h>

#define SUCCESSRETURNCODE 0
#define ERRORCODE 1
int main(int argc, char **argv) {
    try {
        auto app = Gtk::Application::create();

        GameBuilder builder;
        InitialWindow *window = builder.get_initial_window();
        app->run(*window);

        // Once initial window closes, we fetch the socket
        std::shared_ptr<ServerMessenger> m = window->get_socket();
        std::string player_name = window->get_username();
        if (m) {
            ServerMessenger messenger = *m.get();
            MapMonitor mapMonitor;
            UnitsMonitor units_monitor;
            BuildingsMonitor buildingsMonitor;
            ClientThread clientThread(units_monitor, buildingsMonitor,
                                      mapMonitor, messenger, builder);
            clientThread.start();
            bool keep_playing = true;
            while(keep_playing) {
                // Starts the game
                Game g(builder, messenger, player_name, mapMonitor,
                       units_monitor, buildingsMonitor);

                // Game finishes
                keep_playing = g.get_play_again_status();
            }
            clientThread.finish();
            clientThread.join();
        }

        return SUCCESSRETURNCODE;
    } catch (std::exception const &ex) {
        std::cerr << ex.what() << std::endl;
        return ERRORCODE;
    }
}
