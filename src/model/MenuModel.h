/* Copyright 2016-2017 Jolivet Arthur & Laronze Florian

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef MENU_MODEL_H
#define MENU_MODEL_H

#include "Commands.h"
#include "Leaderboard.h"
#include "Settings.h"
#include "Shop.h"
#include "../enum/MenuState.h"
#include <chrono>

/**
 * The MenuModel class
 * handles the menu's logic
 * @author Arthur
 * @date 14/04/16 - 29/01/17
 */
class MenuModel : public AbstractModel
{
public:
    //=== CTORs / DTORs
    MenuModel(DataBase *dataBase);
    virtual ~MenuModel() override;

    //=== GETTERS
    MenuState getMenuState() const;

    //=== SETTERS
    void setMenuState(MenuState state);

    //=== METHODS
    virtual void nextStep() override;
    Commands* launchCommands();
    Leaderboard* launchLeaderboard();
    Shop* launchShop();
    Settings* launchSettings();

private:
    //=== ATTRIBUTES
    MenuState m_menuState;
    Commands *m_commands;
    Leaderboard *m_leaderboard;
    Settings *m_settings;
    Shop *m_shop;
    std::chrono::system_clock::time_point m_lastTime;
};

#endif
