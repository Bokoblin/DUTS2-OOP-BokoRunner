/* Copyright 2016-2019 Jolivet Arthur & Laronze Florian

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

#include "app/model/models/MenuModel.h"
#include "AbstractView.h"
#include "CommandsView.h"
#include "LeaderboardView.h"
#include "SettingsView.h"
#include "ShopView.h"
#include "app/view/ui-components/ParallaxBackground.h"

/**
 * @class MenuView
 *
 * @author Arthur, Florian
 * @date 26/03/2016 - 14/07/2019
 */
class MenuView: public AbstractView
{
public:
    //=== CTORs / DTORs
    MenuView(sf::RenderWindow* window, AppTextManager* textManager, MenuModel* menuModel);
    ~MenuView() override;

    //=== METHODS
    void synchronize() override;
    void draw() const override;
    bool handleEvents(sf::Event& event) override;

private:
    //=== ATTRIBUTES
    MenuModel* m_menu;
    CommandsView* m_commandsView;
    LeaderboardView* m_leaderboardView;
    SettingsView* m_settingsView;
    ShopView* m_shopView;

    //Graphic Elements
    ParallaxBackground* m_parallaxBackground;
    mdsf::Sprite* m_titleSprite;
    mdsf::RaisedButton* m_playButton;
    mdsf::RaisedButton* m_quitButton;
    mdsf::RaisedButton* m_commandsButton;
    mdsf::RaisedButton* m_settingsButton;
    mdsf::RaisedButton* m_leaderboardButton;
    mdsf::RaisedButton* m_shopButton;

    //Audio
    sf::Music m_menuMusic;

    //Constants
    const int MAIN_BUTTON_WIDTH = 150;
    const int MAIN_BUTTON_HEIGHT = 80;
    const int BACKGROUND_WIDTH = 1200;
    const int FAR_SCROLL_SPEED = 1;
    const int NEAR_SCROLL_SPEED = 2;
    const int MUSIC_LOOP_START = 4851;
    const int MUSIC_LOOP_END = 28840;
    const int HOME_BUTTON_SIZE = 50;
    const int TITLE_WIDTH = 400;
    const int TITLE_HEIGHT = 200;

    //=== METHODS
    void loadMusic();
    void loadSprites() override;
    bool handleHomeEvents(const sf::Event& event);
};

#endif
