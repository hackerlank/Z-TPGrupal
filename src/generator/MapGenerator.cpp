#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include "MapGenerator.h"
#include <pugixml.hpp>
#include <random>

#define UNIT 0
#define VEHICLE 1

#define TERRAIN "terrain"

MapGenerator::MapGenerator(int size, float lava_pct,
                           float water_pct, int territories) :
    size(size),
    lava_pct(lava_pct),
    water_pct(water_pct),
    terr(territories)
{
    for (int i = 0; i < size; ++i) {
        std::vector<bool> row;
        for (int j = 0; j < size; ++j) {
            row.push_back(false);
        }
        liquid_cells.push_back(row);
    }
    water_cells = (int) (size * size * water_pct / 100);
    lava_cells = (int) (size * size * lava_pct / 100);

    /* Adjustment to size to split territories evenly */
    int territories_per_row =  (int) floor(sqrt(terr));
    if (size % territories_per_row) {
        this->size = size - territories_per_row;
    }
}


void MapGenerator::generate_blank_map(pugi::xml_node root_node) {
    for (int i = 0; i < size; ++i) {
        pugi::xml_node row = root_node.append_child("Row");
        for (int j = 0; j < size; ++j) {
            pugi::xml_node cell = row.append_child("Cell");
            pugi::xml_attribute attr = cell.append_attribute(TERRAIN);
            attr.set_value("Tierra");
        }
    }
}


std::vector<std::vector<bool>>
MapGenerator::generate_rivers(pugi::xml_node root_node, int cell_amt,
                                   const std::string &terrain) {
    std::vector<std::vector<bool>> map;
    generate_path(cell_amt, map);
    int count_y = 0;
    for (pugi::xml_node& row : root_node.children()) {
        int count_x = 0;
        for (pugi::xml_node& node : row.children()) {
            if (map[count_x][count_y]) {
                node.attribute(TERRAIN).set_value(terrain.c_str());
            }
            count_x++;
        }
        count_y++;
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; ++j) {
            if (map[i][j]) {
                liquid_cells[i][j] = true;
            }
        }
    }
    return map;
}


void MapGenerator::generate_path(int amt,
                                 std::vector<std::vector<bool>>& path) {
    for (int i = 0; i < size; ++i) {
        std::vector<bool> row;
        for (int j = 0; j < size; ++j) {
            row.push_back(false);
        }
        path.push_back(row);
    }

    int river_x = r.generate() % size;
    int river_y = r.generate() % size;

    while (amt) {
        path[river_x][river_y] = true;

        bool found = false;

        while (!found) {
            int end = r.generate() % 100;
            if (end < RIVER_END_PCT) { // Start another river somewhere else
                river_x = r.generate() % size;
                river_y = r.generate() % size;
            }
            // Grab an adjacent tile randomly to be the next water tile
            int next = r.generate() % 4;
            int next_x, next_y;
            if (next == 0) {
                next_x = 1;
                next_y = 0;
            } else if (next == 1) {
                next_x = 0;
                next_y = -1;
            } else if (next == 2) {
                next_x = -1;
                next_y = 0;
            } else {
                next_x = 0;
                next_y = 1;
            }
            next_x += river_x;
            next_y += river_y;


            // Check for out of bounds
            if (!(next_x > 0 && next_y > 0 && next_x < size && next_y < size)) {
                continue;
            }

            if (!path[next_x][next_y]) {
                found = true;
                amt--;
                river_x = next_x;
                river_y = next_y;
            }
        }
    }
}


void MapGenerator::generate_rocks(pugi::xml_node root) {
    root.set_name("Structures");
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (!liquid_cells[i][j]) {
                int chance = r.generate() % 100;
                if (chance < ROCK_PCT) {
                    pugi::xml_node rock = root.append_child("Struct");
                    rock.append_attribute("Type").set_value("Rock");
                    rock.append_attribute("x").set_value(i);
                    rock.append_attribute("y").set_value(j);
                }
            }
        }
    }
}


void MapGenerator::generate(const std::string& name) {
    std::string path = "maps/" + name + ".xml";
    pugi::xml_document document;
    pugi::xml_node root = document.append_child("Map");
    pugi::xml_node terrain = root.append_child("Terrain");
    generate_blank_map(terrain);

    generate_territories(root);
    generate_rivers(terrain, water_cells, "Agua");
    generate_rivers(terrain, lava_cells, "Lava");


    pugi::xml_node structs = root.append_child("Structs");
    generate_rocks(structs);
    bool saved = document.save_file(path.c_str());
    if (!saved) {
        std::cout << "Error saving map to " << path << std::endl;
    }
}


void MapGenerator::generate_territories(pugi::xml_node root) {
    pugi::xml_node forts = root.append_child("Territories");

    /* Choose exactly FORTS_AMT of territories to be designed as central.
     * There's one fort for each expected player in the map */
    int fort_territories[FORTS_AMT];
    for (int k = 0; k < FORTS_AMT; ++k) {
        bool found = false;
        while (!found) {
            int position = r.generate() % terr;
            bool repeat = false;
            for (int i = 0; i < k; ++i) {
                if (fort_territories[i] == position) {
                    repeat = true;
                }
            }
            if (repeat) {
                continue;
            }
            fort_territories[k] = position;
            found = true;
        }
    }

    double size_sqrt =  sqrt(terr);
    int territories_x = (int) floor(size_sqrt);
    int territories_y = (int) ceil(size_sqrt);

    int div_x = size / territories_x;
    int div_y = size / territories_y;
    int count = 0;
    for (int i = 0; i < territories_y; ++i) {
        for (int j = 0; j < territories_x; ++j) {
            /* Randomize positions in the territories */
            int terr_min_x = div_x * j,
                terr_min_y = div_y * i,
                terr_max_x = div_x * (j + 1) - 1,
                terr_max_y = div_y * (i + 1) - 1;

            std::string name = "Flag";
            for (int k = 0; k < FORTS_AMT; ++k) {
                if (fort_territories[k] == count) {
                    name = "Fort";
                }
            }

            bool found = false;
            int flag_x = 0;
            int flag_y = 0;

            while (!found) {
                flag_x = terr_min_x + r.generate() % (size / terr);
                flag_y = terr_min_y + r.generate() % (size / terr);
                if (!liquid_cells[flag_x][flag_y]) {
                    found = true;
                }
            }
            pugi::xml_node flag = forts.append_child(name.c_str());
            flag.append_attribute("center_x").set_value(flag_x);
            flag.append_attribute("center_y").set_value(flag_y);
            flag.append_attribute("min_x").set_value(terr_min_x);
            flag.append_attribute("min_y").set_value(terr_min_y);
            flag.append_attribute("max_x").set_value(terr_max_x);
            flag.append_attribute("max_y").set_value(terr_max_y);

            pugi::xml_node map = root.child("Terrain");
            generate_factories(flag, terr_min_x, terr_min_y, terr_max_x,
                               terr_max_y, map);
            count ++;
        }
    }
}

void MapGenerator::generate_factories(pugi::xml_node &territory, int min_x,
                                      int min_y, int max_x,
                                      int max_y, pugi::xml_node &map) {
    int territories = 2;
    for (int i = 0; i < territories; ++i) {
        bool found = false;
        while(!found) {
            /* Randomize the position, inside the territory */
            int fact_x = r.generate() % (max_x - min_x) + min_x;
            int fact_y = r.generate() % (max_y - min_y) + min_y;

            /* Select type: unit or vehicle */
            int unit_or_vehicle_factory = r.generate() % 2;
            std::string type;
            if (unit_or_vehicle_factory == UNIT) {
                type = "UnitFactory";
            } else if (unit_or_vehicle_factory == VEHICLE) {
                type = "VehicleFactory";
            }

            int count_x = 0;
            for (pugi::xml_node row : map.children()) {
                int count_y = 0;
                for (pugi::xml_node cell : row.children()) {
                    if (fact_x == count_x && fact_y == count_y) {
                        const char* terrain = cell.attribute(TERRAIN).value();
                        if (!liquid_cells[fact_x][fact_y]) {
                            pugi::xml_node factory =
                                    territory.append_child(type.c_str());
                            factory.append_attribute("x").set_value(fact_x);
                            factory.append_attribute("y").set_value(fact_y);
                            found = true;
                            break;
                        }
                    }
                    count_y++;
                }
                if (found) {
                    break;
                }
                count_x++;
            }

        }
    }
}

MapGenerator::~MapGenerator() {
    if (output.is_open()) {
        output.close();
    }
}
