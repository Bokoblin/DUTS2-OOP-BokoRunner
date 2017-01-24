cmake_minimum_required(VERSION 3.5)

#Configuration du projet
set(PROJECT_NAME runner)
project(${PROJECT_NAME})
set(EXECUTABLE_NAME ${PROJECT_NAME})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#include libraries
set(SFML_ROOT "${PROJECT_SOURCE_DIR}/libs/SFML-2.3.2")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${SFML_ROOT}/cmake/Modules/")

set(SOURCE_FILES
        libs/pugixml-1.8/src/pugixml.hpp
        libs/pugixml-1.8/src/pugixml.cpp
        src/model/Bonus.cpp
        src/model/Bonus.h
        src/model/Coin.cpp
        src/model/Coin.h
        src/model/Commands.cpp
        src/model/Commands.h
        src/model/DataBase.cpp
        src/model/DataBase.h
        src/model/Enemy.cpp
        src/model/Enemy.h
        src/model/GameModel.cpp
        src/model/GameModel.h
        src/model/Leaderboard.cpp
        src/model/Leaderboard.h
        src/model/MenuModel.cpp
        src/model/MenuModel.h
        src/model/Model.cpp
        src/model/Model.h
        src/model/MovableElement.cpp
        src/model/MovableElement.h
        src/model/Player.cpp
        src/model/Player.h
        src/model/Settings.cpp
        src/model/Settings.h
        src/model/Shop.cpp
        src/model/Shop.h
        src/model/ShopItem.cpp
        src/model/ShopItem.h
        src/view/AnimatedGraphicElement.cpp
        src/view/AnimatedGraphicElement.h
        src/constants.h
        src/view/Button.cpp
        src/view/Button.h
        src/view/CommandsView.cpp
        src/view/CommandsView.h
        src/view/Dialog.cpp
        src/view/Dialog.h
        src/view/GameView.cpp
        src/view/GameView.h
        src/view/GraphicElement.cpp
        src/view/GraphicElement.h
        src/view/Intro.cpp
        src/view/Intro.h
        src/view/LeaderboardView.cpp
        src/view/LeaderboardView.h
        src/view/MenuView.cpp
        src/view/MenuView.h
        src/view/PixelateEffect.cpp
        src/view/PixelateEffect.h
        src/view/SettingsView.cpp
        src/view/SettingsView.h
        src/view/ShopItemCard.cpp
        src/view/ShopItemCard.h
        src/view/ShopView.cpp
        src/view/ShopView.h
        src/view/SlidingBackground.cpp
        src/view/SlidingBackground.h
        src/view/TextHandler.cpp
        src/view/TextHandler.h
        src/view/View.cpp
        src/view/View.h
        src/view/Text.cpp
        src/view/Text.h
        src/view/RadioButton.cpp
        src/view/RadioButton.h
        src/main.cpp)

add_executable(runner ${SOURCE_FILES})

FIND_PACKAGE(SFML 2 COMPONENTS system window graphics audio REQUIRED)

include_directories( ${SFML_INCLUDE_DIR} )
target_link_libraries( ${EXECUTABLE_NAME} ${SFML_LIBRARIES})