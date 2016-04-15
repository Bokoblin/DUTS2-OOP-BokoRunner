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

#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include "View.h"

/********************************************
    Constant Variables
********************************************/
//GAME
const std::string BOTTOM_BAR = "Images/bottom_bar.png";
const std::string LIFE_BOX = "Images/life_bar.png";
const std::string REMAINING_LIFE = "Images/remaining_life.png";
const std::string BALL_IMAGE = "Images/balls.png";
const std::string ENEMIES_IMAGE = "Images/enemies.png";
const std::string BONUS_IMAGE = "Images/bonus.png";
//PAUSE
const std::string PAUSE_BACKGROUND_IMAGE = "Images/pause_background.png";
const std::string PAUSE_BUTTONS_IMAGE = "Images/pause_elements.png";
//END
const std::string END_BACKGROUND_IMAGE = "Images/end_background.png";

/********************************************
    GameView Class
*********************************************
    @author Arthur  @date 21/02 - 12/04
    @author Florian @date 21/02 - 3/03
*********************************************/
class GameView : public View
{
public:
	//=== CTORs / DTORs
	GameView(float w, float h, sf::RenderWindow *window, Text *text);
	virtual ~GameView();

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
    //=== ATTRIBUTES
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
    sf::Texture m_PVPlusBonusTexture;
    sf::Texture m_megaBonusTexture;
    sf::Texture m_flyBonusTexture;
    sf::Texture m_slowSpeedBonusTexture;
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
    AnimatedGraphicElement *m_PVPlusBonusGraphic;
    AnimatedGraphicElement *m_megaBonusGraphic;
    AnimatedGraphicElement *m_flyBonusGraphic;
    AnimatedGraphicElement *m_slowSpeedBonusGraphic;
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


#endif // GAMEVIEW_H
