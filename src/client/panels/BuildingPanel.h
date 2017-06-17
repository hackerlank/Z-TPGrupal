#ifndef Z_TPGRUPAL_BUILDINGPANEL_H
#define Z_TPGRUPAL_BUILDINGPANEL_H


#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include <gtkmm/builder.h>
#include <string>
#include <gtkmm/button.h>

class BuildingPanel : public Gtk::Box {
    Gtk::Image* building;
    Gtk::Image* unit;
    const std::string label = "Factory";
    Gtk::Button* prev;
    Gtk::Button* next;
    Gtk::Button* create;
public:
    BuildingPanel(BaseObjectType* cobject,
                  const Glib::RefPtr<Gtk::Builder>& builder);

    const std::string& get_label();
    Gtk::Button* next_button();
    Gtk::Button* create_button();
    void on_click();
    void change_unit(std::string& path);
};


#endif //Z_TPGRUPAL_BUILDINGPANEL_H
