cmake_minimum_required(VERSION 3.5)

#Configuration du projet
set(PROJECT_NAME runner)
project(${PROJECT_NAME})
set(EXECUTABLE_NAME ${PROJECT_NAME})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#include libraries
set(SFML_ROOT "${PROJECT_SOURCE_DIR}/Libs/SFML-2.3.2")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${SFML_ROOT}/cmake/Modules/")

set(SOURCE_FILES
    Libs/pugixml-1.7/src/pugixml.hpp
    Libs/pugixml-1.7/src/pugixml.cpp
    Sources/AnimatedGraphicElement.cpp
    Sources/AnimatedGraphicElement.h
    Sources/Bonus.cpp
    Sources/Bonus.h
    Sources/Button.cpp
    Sources/Button.h
    Sources/Coin.cpp
    Sources/Coin.h
    Sources/DataBase.cpp
    Sources/DataBase.h
    Sources/Dialog.cpp
    Sources/Dialog.h
    Sources/Enemy.cpp
    Sources/Enemy.h
    Sources/GameModel.cpp
    Sources/GameModel.h
    Sources/GameView.cpp
    Sources/GameView.h
    Sources/GraphicElement.cpp
    Sources/GraphicElement.h
    Sources/ImagesConstants.h
    Sources/Intro.cpp
    Sources/Intro.h
    Sources/Leaderboard.cpp
    Sources/Leaderboard.h
    Sources/LeaderboardView.cpp
    Sources/LeaderboardView.h
    Sources/main.cpp
    Sources/MenuModel.cpp
    Sources/MenuModel.h
    Sources/MenuView.cpp
    Sources/MenuView.h
    Sources/Model.cpp
    Sources/Model.h
    Sources/MovableElement.cpp
    Sources/MovableElement.h
    Sources/PixelateEffect.cpp
    Sources/PixelateEffect.h
    Sources/Player.cpp
    Sources/Player.h
    Sources/Settings.cpp
    Sources/Settings.h
    Sources/SettingsView.cpp
    Sources/SettingsView.h
    Sources/Shop.cpp
    Sources/Shop.h
    Sources/ShopItem.cpp
    Sources/ShopItem.h
    Sources/ShopItemCard.cpp
    Sources/ShopItemCard.h
    Sources/ShopView.cpp
    Sources/ShopView.h
    Sources/SlidingBackground.cpp
    Sources/SlidingBackground.h
    Sources/Text.cpp
    Sources/Text.h
    Sources/View.cpp
    Sources/View.h
        )

add_executable(runner ${SOURCE_FILES})

FIND_PACKAGE(SFML 2 COMPONENTS system window graphics audio REQUIRED)

include_directories( ${SFML_INCLUDE_DIR} )
target_link_libraries( ${EXECUTABLE_NAME} ${SFML_LIBRARIES})