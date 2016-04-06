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

#ifndef GAME_H
#define GAME_H

#include "View.h"
#include "GameModel.h"
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <string>
#include <set>
#include <cassert>
#include <ctime>
#include "SFML/Graphics.hpp"
#include "SlidingBackground.h"
#include "AnimatedGraphicElement.h"
#include "Button.h"

#define MOUSE_POSITION sf::Vector2f(event.mouseButton.x, event.mouseButton.y)

/********************************************
    Constant Variables
********************************************/
//GAME
const std::string BOTTOM_BAR = "Images/bottom_bar.png";
const std::string LIFE_BOX = "Images/life.png";
const std::string REMAINING_LIFE = "Images/remaining_life.png";
const std::string BALL_IMAGE = "Images/balls.png";
const std::string ENEMIES_IMAGE = "Images/enemies.png";
const std::string BONUS_IMAGE = "Images/bonus.png";
//PAUSE
const std::string PAUSE_BACKGROUND_IMAGE = "Images/pause_background.png";
const std::string PAUSE_BUTTONS_IMAGE = "Images/pause_elements.png";
//END
const std::string END_BACKGROUND_IMAGE = "Images/end_background.png";

class GameModel;
class Model;

/********************************************
    GameView Class
*********************************************
    Arthur : 21/02 - 31/03
    Florian: 21/02 - 3/03
*********************************************/
class GameView : public View
{
public:
    //=== CTORs / DTORs
    GameView(unsigned int w, unsigned int h, sf::RenderWindow *mywindow);
    ~GameView();

    //=== SETTERS
    void setGameModel(GameModel *model);

    //=== METHODS
    virtual void loadImages() override;
    virtual void synchronize() override;
    virtual void draw() const override;
    virtual bool treatEvents() override;
    virtual void linkElements();
    virtual void updateElements();
    virtual void deleteElements();

private:
    GameModel *m_gameModel;

    //Game Textures
    sf::Texture m_farBackgroundTexture;
    sf::Texture m_nearBackgroundTexture;
    sf::Texture m_bottomBarTexture;
    sf::Texture m_lifeBoxTexture;
    sf::Texture m_remainingLifeTexture;
    sf::Texture m_playerTexture;
    sf::Texture m_standardEnemyTexture;
    sf::Texture m_totemEnemyTexture;
    sf::Texture m_blockEnemyTexture;
    sf::Texture m_coinTexture;
    sf::Texture m_explosionTexture;
    //Pause menu Textures
    sf::Texture m_pauseBackgroundTexture;
    sf::Texture m_resumeButtonTexture;
    sf::Texture m_restartButtonTexture;
    sf::Texture m_homeButtonTexture;
    sf::Texture m_pauseDistanceTexture;
    sf::Texture m_endBackgroundTexture;

    //Game Graphic Elements
    SlidingBackground *m_farBackground;
    SlidingBackground *m_nearBackground;
    GraphicElement *m_bottomBarGraphic;
    GraphicElement *m_lifeBoxGraphic;
    GraphicElement *m_remainingLifeGraphic;
    AnimatedGraphicElement *m_playerGraphic;
    AnimatedGraphicElement *m_standardEnemyGraphic;
    AnimatedGraphicElement *m_totemEnemyGraphic;
    AnimatedGraphicElement *m_blockEnemyGraphic;
    AnimatedGraphicElement *m_coinGraphic;
    AnimatedGraphicElement *m_explosionGraphic;
    //Pause and End Graphic Elements
    GraphicElement *m_pauseBackgroundGraphic;
    GraphicElement *m_pauseDistanceGraphic;
    GraphicElement *m_endBackgroundGraphic;
    Button *m_resumeButtonGraphic;
    Button *m_restartButtonGraphic;
    Button *m_homeButtonGraphic;

    //Containers
    std::map<MovableElement*, GraphicElement*> m_MovableToGraphicElement;
};


#endif // GAME_H
