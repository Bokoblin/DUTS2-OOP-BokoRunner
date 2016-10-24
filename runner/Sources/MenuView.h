/* Copyright 2016 Jolivet Arthur & Laronze Florian

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

#ifndef MENUVIEW_H
#define MENUVIEW_H

#include "View.h"
#include "MenuModel.h"
#include "LeaderboardView.h"
#include "SettingsView.h"
#include "ShopView.h"


/********************************************
    Constant Variables
********************************************/
const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 600;

const std::string MENU_MUSIC = "Music/menu_sound.ogg";

/********************************************
    MenuView Class
*********************************************
    @author Arthur  @date 26/03 - 21/05
    @author Florian @date 20/04 - 03/05
*********************************************/
class MenuView : public View
{
public:
    //=== CTORs / DTORs
    MenuView(float w, float h, sf::RenderWindow *window, Text * text);
    virtual ~MenuView();

    //=== SETTERS
	void setMenuModel(MenuModel *model);

    //=== METHODS
    virtual void synchronize() override;
    virtual void draw() const override;
    virtual void loadImages() override;
    virtual bool treatEvents() override;

private:
    //=== ATTRIBUTES
    MenuModel *m_menuModel;
    LeaderboardView *m_leaderboardView;
    SettingsView *m_settingsView;
    ShopView *m_shopView;

    //Textures
    sf::Texture m_farBackgroundTexture;
    sf::Texture m_nearBackgroundTexture;
    sf::Texture m_titleImageTexture;
    sf::Texture m_menuRectButtonsTexture;
    sf::Texture m_menuFormButtonsTexture;

    //Graphic Elements
    SlidingBackground *m_farBackground;
    SlidingBackground *m_nearBackground;
    GraphicElement *m_titleGraphic;
    Button *m_playRectButton;
    Button *m_quitRectButton;
    Button *m_settingsFormButton;
    Button *m_leaderboardFormButton;
    Button *m_shopFormButton;

    //Music
    sf::Music m_menuMusic;
};

#endif