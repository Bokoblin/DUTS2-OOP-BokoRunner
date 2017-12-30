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

#ifndef MENU_VIEW_H
#define MENU_VIEW_H

#include "View.h"
#include "../model/MenuModel.h"
#include "CommandsView.h"
#include "LeaderboardView.h"
#include "SettingsView.h"
#include "ShopView.h"


/**
 * MenuView Class
 * @author Arthur, Florian
 * @date 26/03/16 - 24/01/17
 */
class MenuView : public View
{
public:
    //=== CTORs / DTORs
    MenuView(float w, float h, sf::RenderWindow *window, TextHandler *textHandler);
    ~MenuView() override;

    //=== SETTERS
	void setMenuModel(MenuModel *model);

    //=== METHODS
    void synchronize() override;
    void draw() const override;
    void loadImages() override;
    bool treatEvents() override;

private:
    //=== ATTRIBUTES
    MenuModel *m_menuModel;
    CommandsView *m_commandsView;
    LeaderboardView *m_leaderboardView;
    SettingsView *m_settingsView;
    ShopView *m_shopView;

    //Graphic Elements
    SlidingBackground *m_farBackground;
    SlidingBackground *m_nearBackground;
    GraphicElement *m_titleGraphic;
    Button *m_playRectButton;
    Button *m_quitRectButton;
    Button *m_commandsFormButton;
    Button *m_settingsFormButton;
    Button *m_leaderboardFormButton;
    Button *m_shopFormButton;

    //Audio
    sf::Music m_menuMusic;
};

#endif