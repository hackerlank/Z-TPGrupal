#include <gtkmm/window.h>
#include "GraphicsThread.h"
#include "GameBuilder.h"
#include "BuildingsMonitor.h"
#include "MapMonitor.h"
#include "ServerMessenger.h"

void GraphicsThread::run() {
    auto app = Gtk::Application::create();

    window.change_view_to_unit();
    window.setResources(&unitsMonitor,
                         &buildingsMonitor,
                         &mapMonitor,
                         &messenger);
    app->run(window);
    //todo check exit status. Couldn't find exit status codes,
    //so don't know what each number means

}

GraphicsThread::GraphicsThread(UnitsMonitor &monitor,
                               BuildingsMonitor &buildingsMonitor,
                               MapMonitor &mapMonitor,
                               ServerMessenger &messenger,
                               GameWindow& window) :
        unitsMonitor(monitor),
        buildingsMonitor(buildingsMonitor),
        mapMonitor(mapMonitor),
        messenger(messenger),
        window(window)
{
}
