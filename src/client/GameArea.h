#ifndef Z_TPGRUPAL_GAMEAREA_H
#define Z_TPGRUPAL_GAMEAREA_H


#include <gtkmm/drawingarea.h>
#include <utility>
#include "PlayersMonitor.h"
#include "BuildingsMonitor.h"
#include "MapMonitor.h"
#include "Camera.h"
#include "FlagEnum.h"
#include "TeamEnum.h"
#include "ActionsEnum.h"
#include "UnitsEnum.h"
#include "BuildingsEnum.h"
#include <map>
#include <string>
#include <vector>

class GameArea : public Gtk::DrawingArea{
public:
    virtual ~GameArea();
    GameArea(BaseObjectType* cobject,
             const Glib::RefPtr<Gtk::Builder>& builder);

    /**
     * initialize shared resources.
     */
    void
    setResources(PlayersMonitor *playersMonitor,
                 BuildingsMonitor *buildingsMonitor,
                 MapMonitor *mapMonitor);

protected:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

private:
    /* shared resources */
    PlayersMonitor *playersMonitor;
    BuildingsMonitor *buildingsMonitor;
    MapMonitor *mapMonitor;

    Camera camera;

    /* general resources */
    std::map<std::string, Glib::RefPtr<Gdk::Pixbuf>> tiles;

    Glib::RefPtr<Gdk::Pixbuf> someImg;

    /* map holding all flags */
    std::map<FlagEnum, std::vector<Glib::RefPtr<Gdk::Pixbuf>>> flags;

    /* map holding all units' fire animations */
    std::map<TeamEnum,
            std::map<UnitsEnum,
                    std::map<ActionsEnum,
                            std::vector<Glib::RefPtr<Gdk::Pixbuf>>>>>
            unitsFireAnimations;

    /* map holding all units' walking and standing animations.
     * In this animations robots are not shown differently */
    std::map<TeamEnum ,
            std::map<ActionsEnum,
                    std::vector<Glib::RefPtr<Gdk::Pixbuf>>>>
            unitsGeneralAnimations;

    /* BUILDINGS RESOURCES */
    std::map<BuildingsEnum, std::vector<Glib::RefPtr<Gdk::Pixbuf>>> buildings;

    /* VEHICLES RESOURCES */
    std::map<TeamEnum ,
            std::map<UnitsEnum ,
                    std::vector<Glib::RefPtr<Gdk::Pixbuf>>>> vehicleBases;

    std::map<UnitsEnum, std::vector<Glib::RefPtr<Gdk::Pixbuf>>> tires;

    /* declare counter used to know which of the flag imgs
     * which compose the flag's animation should be showed */
    unsigned long flagCounter;
    unsigned short jeepCounter;
    unsigned short tireCounter;
    unsigned short lightTankCounter;

    /* DRAWING METHODS */
    void drawBaseMap(const Cairo::RefPtr<Cairo::Context> &cr,
                     std::pair<unsigned int, unsigned int> cameraPosition);

    void drawTileAt(const Cairo::RefPtr<Cairo::Context> &cr,
                    unsigned int xCoordinate, unsigned int yCoordinate,
                    std::string terrainType);

    void drawFlagAnimation(const Cairo::RefPtr<Cairo::Context> &ptr,
                           int xCoordinate, int yCoordinate);

    void displaySomeStaticImg(const Cairo::RefPtr<Cairo::Context> &refPtr,
                              int xCoordinate, int yCoordinate);

    /* JEEP DRAWINGS */
    /* BLUE JEEP */
    void drawBlueJeep000(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawBlueJeep045(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawBlueJeep090(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawBlueJeep135(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawBlueJeep180(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawBlueJeep225(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawBlueJeep270(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawBlueJeep315(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    /* GREEN JEEP */
    void drawGreenJeep000(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawGreenJeep045(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawGreenJeep090(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawGreenJeep135(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawGreenJeep180(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawGreenJeep225(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawGreenJeep270(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawGreenJeep315(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    /* RED JEEP */
    void drawRedJeep000(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawRedJeep045(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawRedJeep090(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawRedJeep135(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawRedJeep180(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawRedJeep225(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawRedJeep270(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawRedJeep315(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    /* YELLOW JEEP */
    void drawYellowJeep000(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawYellowJeep045(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawYellowJeep090(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawYellowJeep135(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawYellowJeep180(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawYellowJeep225(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawYellowJeep270(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawYellowJeep315(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    /* TANKS DRAWINGS */
    /* LIGHT TANK */
    /* BLUE LIGHT TANK DRAWING */
    void drawBlueLightTank000(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawBlueLightTank045(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawBlueLightTank090(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawBlueLightTank135(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawBlueLightTank180(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawBlueLightTank225(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawBlueLightTank270(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawBlueLightTank315(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    /* GREEN LIGHT TANK DRAWING */
    void drawGreenLightTank000(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawGreenLightTank045(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawGreenLightTank090(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawGreenLightTank135(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawGreenLightTank180(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawGreenLightTank225(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawGreenLightTank270(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawGreenLightTank315(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    /* RED LIGHT TANK DRAWING */
    void drawRedLightTank000(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawRedLightTank045(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawRedLightTank090(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawRedLightTank135(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawRedLightTank180(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawRedLightTank225(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawRedLightTank270(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawRedLightTank315(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    /* YELLOW LIGHT TANK DRAWING */
    void drawYellowLightTank000(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawYellowLightTank045(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawYellowLightTank090(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawYellowLightTank135(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawYellowLightTank180(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawYellowLightTank225(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawYellowLightTank270(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    void drawYellowLightTank315(const Cairo::RefPtr<Cairo::Context> &cr,
                         unsigned int xCoordinate, unsigned int yCoordinate);

    /* Event handling methods */
    bool on_key_press_event(GdkEventKey *event) override;

    bool on_button_press_event(GdkEventButton *event) override;

    bool on_button_release_event(GdkEventButton *event) override;

    /* vars. for event handling */
    gdouble xStartCoordinate;
    gdouble xFinishCoordinate;
    gdouble yStartCoordinate;
    gdouble yFinishCoordinate;
    bool selectionMade;

    void processSelection();

    /* FLAG res loading */
    void loadFlagAnimations();

    /* UNIT FIRE res loading */
    void loadUnitsResources();

    void loadGruntFireAnimations();

    void loadLaserFireAnimations();

    void loadPsychoFireAnimations();

    void loadPyroFireAnimations();

    void loadSniperFireAnimations();

    void loadToughFireAnimations();

    void loadBlueGruntFireAnimations();

    void loadRedGruntFireAnimations();

    void loadYellowGruntFireAnimations();

    void loadBlueLaserFireAnimations();

    void loadGreenLaserFireAnimations();

    void loadRedLaserFireAnimations();

    void loadYellowLaserFireAnimations();

    void loadBluePsychoFireAnimations();

    void loadGreenPsychoFireAnimations();

    void loadRedPsychoFireAnimations();

    void loadYellowPsychoFireAnimations();

    void loadBlueSniperFireAnimations();

    void loadGreenSniperFireAnimations();

    void loadRedSniperFireAnimations();

    void loadYellowSniperFireAnimations();

    void loadBlueToughFireAnimations();

    void loadGreenToughFireAnimations();

    void loadRedToughFireAnimations();

    void loadYellowToughFireAnimations();

    /* UNIT WALK res loading */
    void loadBlueWalkingAnimations();

    void loadGreenWalkingAnimations();

    void loadRedWalkingAnimations();

    void loadYellowWalkingAnimations();

    /* UNIT STAND res loading */
    void loadBlueStandingAnimations();

    void loadGreenStandingAnimations();

    void loadRedStandingAnimations();

    void loadYellowStandingAnimations();

    /* BUILDING res loading */
    void loadBuildingsResources();

    /* VEHICLES res loading */
    void loadTiresAnimations();

    void loadJeepTires();

    void loadNeuterVehiclesAnimations();

    void loadNeuterJeepAnimations();

    void loadBlueVehiclesAnimations();

    void loadGreenVehiclesAnimations();

    void loadRedVehiclesAnimations();

    void loadYellowVehiclesAnimations();

    void loadBlueJeepAnimations();

    void loadBlueLightTankAnimations();

    void loadBlueMediumTankAnimations();

    void loadBlueMMLAnimations();

    void loadBlueHeavyTankAnimations();

    void loadGreenJeepAnimations();

    void loadGreenLightTankAnimations();

    void loadGreenMediumTankAnimations();

    void loadGreenMMLAnimations();

    void loadGreenHeavyTankAnimations();

    void loadRedJeepAnimations();

    void loadRedLightTankAnimations();

    void loadRedMediumTankAnimations();

    void loadRedMMLAnimations();

    void loadRedHeavyTankAnimations();

    void loadYellowJeepAnimations();

    void loadYellowLightTankAnimations();

    void loadYellowMediumTankAnimations();

    void loadYellowMMLAnimations();

    void loadYellowHeavyTankAnimations();
};


#endif //Z_TPGRUPAL_GAMEAREA_H
