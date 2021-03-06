cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 11)
project(Z_TPGrupal)

set(LIBS_DIR libs)
set(PUGI ${LIBS_DIR}/xml)

find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-3.0)
pkg_check_modules(SDL2 sdl2)
pkg_check_modules(SDL2_mixer SDL2_mixer)

link_directories(
        ${SDL2_mixer_LIBRARY_DIRS}
        ${GTKMM_LIBRARY_DIRS}
        ../common)

include_directories(
        ${PUGI}
        ${GTKMM_INCLUDE_DIRS}
        ${SDL2_LIBRARY_DIRS}
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_mixer_INCLUDE_DIRS}
        ../common)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(SOURCE_FILES
        ../../libs/xml/pugixml.hpp
        ../../libs/xml/pugixml.cpp
        windows/GameWindow.cpp
        windows/GameWindow.h
        windows/InitialWindow.cpp
        windows/InitialWindow.h
        Armament.cpp
        Armament.h
        Building.cpp
        Building.h
        panels/BuildingPanel.cpp
        panels/BuildingPanel.h
        BuildingsMonitor.cpp
        BuildingsMonitor.h
        Camera.cpp
        Camera.h
        Cell.cpp
        Cell.h
        ClientThread.cpp
        ClientThread.h
        GameArea.cpp
        GameArea.h
        GameBuilder.cpp
        GameBuilder.h
        main.cpp
        Map.cpp
        Map.h
        MapMonitor.cpp
        MapMonitor.h
        Unit.cpp
        Unit.h ServerMessenger.cpp ServerMessenger.h
        commands/Command.h
        commands/AddUnit.cpp
        commands/AddUnit.h commands/RemoveUnit.cpp commands/RemoveUnit.h commands/UpdateUnit.cpp commands/UpdateUnit.h
        commands/UpdatePosition.cpp commands/UpdatePosition.h enums/TeamEnum.h enums/ActionsEnum.h enums/UnitsEnum.h enums/BuildingsEnum.h commands/LoadMap.cpp commands/LoadMap.h enums/RotationsEnum.h  windows/InitialWindow.cpp windows/InitialWindow.h Counter.cpp Counter.h UnitsMonitor.cpp UnitsMonitor.h panels/UnitPanel.cpp panels/UnitPanel.h commands/FactoryNextUnit.cpp commands/FactoryNextUnit.cpp commands/FactoryNextUnit.h commands/AddBuilding.cpp commands/AddBuilding.h commands/AddNature.cpp commands/AddNature.h windows/LobbyWindow.cpp windows/LobbyWindow.h Nature.cpp Nature.h enums/NatureEnum.h commands/StartGame.cpp commands/StartGame.h commands/PlayerNames.cpp commands/PlayerNames.h commands/UpdateFactory.cpp commands/UpdateFactory.h commands/FactoryStats.cpp commands/FactoryStats.h windows/MenuWindow.cpp windows/MenuWindow.h commands/LobbyInfo.cpp commands/LobbyInfo.h commands/UpdateTerritory.cpp commands/UpdateTerritory.h commands/JoinLobby.cpp commands/JoinLobby.h windows/ResultWindow.cpp windows/ResultWindow.h Game.cpp Game.h commands/Loser.cpp commands/Loser.h commands/Winner.cpp commands/Winner.h commands/MapsInfo.cpp commands/MapsInfo.h)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
add_compile_options(${SDL2_mixer_LDFLAGS} ${SDL2_mixer_CFLAGS})
add_executable(Z_Client ${SOURCE_FILES})

target_link_libraries(Z_Client
        ${GTKMM_LIBRARIES}
        ${SDL_LIBRARY}
        ${SDL2_mixer_LIBRARIES}
        Threads::Threads
        common)