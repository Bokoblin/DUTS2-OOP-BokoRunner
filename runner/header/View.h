/* Copyright (C) 2016 Jolivet Arthur & Laronze Florian

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef _VIEW_H
#define _VIEW_H

#include "Model.h"
#include "../header/SlidingBackground.h"
#include "../header/AnimatedGraphicElement.h"
#include <SFML/Graphics.hpp>

#include <cstdlib>
#include <sstream>
#include <iostream>
#include <string>

#define PLAYER m_model ->getPlayer()


/********************************************
    Constant Variables
********************************************/
const std::string FONT = "Fonts/Antique_Olive.ttf";
const std::string BACKGROUND_IMAGE_1 = "Images/city_1.png";
const std::string BACKGROUND_IMAGE_2 = "Images/city_2.png";
const std::string TITLE_IMAGE = "Images/title.png";
const std::string BUTTONS_IMAGE = "Images/buttons.png";
//Game Only
const std::string BOTTOM_BAR = "Images/bottom_bar.png";
const std::string LIFE_BOX = "Images/life.png";
const std::string REMAINING_LIFE = "Images/remaining_life.png";
const std::string BALL_IMAGE = "Images/balls.png";
const std::string ENEMIES_IMAGE = "Images/enemies.png";
const std::string BONUS_IMAGE = "Images/bonus.png";
const std::string BLOCK_ENEMIES_IMAGE = "Images/enemy_block.png";
const std::string EXPLOSION_IMAGE = "Images/explosion.png";


class Model;

/********************************************
    View Class
*********************************************
    Arthur : 21/02 - 25/03
    Florian: 21/02 - 3/03
*********************************************/
class View
{
public:
    //=== CTORs / DTORs
    View(int w, int h);
    ~View();

    //=== SETTERS
    void setModel(Model *model);

    //=== METHODS
    void synchronize();
    void draw();
    bool treatEvents();

private:
    void loadImages();
    void loadText();
    void linkElements();
    void updateElements();
    void deleteElements();

    //=== ATTRIBUTES
    int m_viewWidth, m_viewHeight;

    sf::RenderWindow *m_window;
    Model *m_model;

    //Text
    sf::Font *m_font;
    sf::Text m_scoreText;
    sf::Text m_distanceText;
    sf::Text m_playerLifeText;
    sf::Text m_playButtonText;
    sf::Text m_quitButtonText;


    //Overall Textures
    sf::Texture m_farBackgroundTexture;
    sf::Texture m_nearBackgroundTexture;
    //Menu Textures
    sf::Texture m_titleTexture;
    sf::Texture m_playButtonTexture;
    sf::Texture m_quitButtonTexture;
    //Game Textures
    sf::Texture m_bottomBarTexture;
    sf::Texture m_lifeBoxTexture;
    sf::Texture m_remainingLifeTexture;
    sf::Texture m_playerTexture;
    sf::Texture m_standardEnemyTexture;
    sf::Texture m_totemEnemyTexture;
    sf::Texture m_blockEnemyTexture;
    sf::Texture m_coinTexture;
    sf::Texture m_explosionTexture;
    //Pause Menu Textures
    sf::Texture m_pauseBackgroundTexture;
    sf::Texture m_resumeButtonTexture;
    sf::Texture m_restartButtonTexture;
    sf::Texture m_homeButtonTexture;

    //Overall Graphic Elements
    SlidingBackground *m_farBackground;
    SlidingBackground *m_nearBackground;
    //Menu Graphic Elements
    GraphicElement *m_titleGraphic;
    GraphicElement *m_playButtonGraphic;
    GraphicElement *m_quitButtonGraphic;
    //Game Graphic Elements
    GraphicElement *m_bottomBarGraphic;
    GraphicElement *m_lifeBoxGraphic;
    GraphicElement *m_remainingLifeGraphic;
    AnimatedGraphicElement *m_playerGraphic;
    AnimatedGraphicElement *m_standardEnemyGraphic;
    AnimatedGraphicElement *m_totemEnemyGraphic;
    AnimatedGraphicElement *m_blockEnemyGraphic;
    AnimatedGraphicElement *m_coinGraphic;
    AnimatedGraphicElement *m_explosionGraphic;
    //Pause Menu Graphic Elements
    GraphicElement *m_pauseBackgroundGraphic;
    GraphicElement *m_resumeButtonGraphic;
    GraphicElement *m_restartButtonGraphic;
    GraphicElement *m_homeButtonGraphic;

    //Containers
    std::map<MovableElement*, GraphicElement*> m_MovableToGraphicElement;
};

#endif
