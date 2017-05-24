#ifndef Z_TPGRUPAL_GAMEWINDOW_H
#define Z_TPGRUPAL_GAMEWINDOW_H

#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <gtkmm/button.h>
#include <gtkmm/builder.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include "GameArea.h"
#include "PlayersMonitor.h"
#include "BuildingsMonitor.h"
#include "MapMonitor.h"
#include "BuildingPanel.h"

class GameWindow : public Gtk::Window {
    GameArea* gameArea;
    Gtk::Box* panel;
    Gtk::Box* unit_panel;
    BuildingPanel* building_panel;
    Gtk::Box* group_panel;
    Gtk::Label* panelLabel;

public:
    GameWindow(BaseObjectType* cobject,
               const Glib::RefPtr<Gtk::Builder>& builder);
    virtual ~GameWindow();

    /**
     * Saves resources' monitors and passes them to the gameArea.
     */
    void
    setResources(PlayersMonitor *playersMonitor,
                 BuildingsMonitor *buildingsMonitor,
                 MapMonitor *mapMonitor);
    // Functions to change the window's side panel
    bool change_view_to_unit();
    bool change_view_to_building();
    bool change_view_to_unit_group();

protected:
    bool onTimeout();

private:
    PlayersMonitor *playersMonitor;
    BuildingsMonitor *buildingsMonitor;
    MapMonitor *mapMonitor;
};

#endif //Z_TPGRUPAL_GAMEWINDOW_H
