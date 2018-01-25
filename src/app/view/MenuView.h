/* Copyright 2016-2018 Jolivet Arthur & Laronze Florian

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

#include "app/model/MenuModel.h"
#include "app/view/AbstractView.h"
#include "app/view/CommandsView.h"
#include "app/view/LeaderboardView.h"
#include "app/view/SettingsView.h"
#include "app/view/ShopView.h"

/**
 * MenuView Class
 * @author Arthur, Florian
 * @date 26/03/16 - 27/12/17
 */
class MenuView : public AbstractView
{
public:
    //=== CTORs / DTORs
    MenuView(sf::RenderWindow *window, AppTextManager *textManager, MenuModel *menuModel);
    ~MenuView() override;

    //=== METHODS
    void synchronize() override;
    void draw() const override;
    bool handleEvents(sf::Event event) override;

private:
    //=== ATTRIBUTES
    MenuModel *m_menu;
    CommandsView *m_commandsView;
    LeaderboardView *m_leaderboardView;
    SettingsView *m_settingsView;
    ShopView *m_shopView;

    //Graphic Elements
    ScrollingBackground *m_farBackground;
    ScrollingBackground *m_nearBackground;
    mdsf::Sprite *m_titleGraphic;
    mdsf::Button *m_playRectButton;
    mdsf::Button *m_quitRectButton;
    mdsf::Button *m_commandsFormButton;
    mdsf::Button *m_settingsFormButton;
    mdsf::Button *m_leaderboardFormButton;
    mdsf::Button *m_shopFormButton;

    //Audio
    sf::Music m_menuMusic;

    //=== METHODS
    void loadMusic();
    void loadImages() override;
    bool handleHomeEvents(const sf::Event &event);
};

#endif
