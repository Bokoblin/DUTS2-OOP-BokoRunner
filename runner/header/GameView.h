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

#include <cmath>
#include "PixelateEffect.h"
#include "View.h"


/********************************************
    Constant Variables
********************************************/
//GAME
const std::string BALL_IMAGE = "Images/balls.png";
const std::string ENEMIES_IMAGE = "Images/enemies.png";
const std::string BONUS_IMAGE = "Images/bonus.png";
const std::string BOTTOM_BAR_IMAGE = "Images/bottom_bar.png";
const std::string LIFE_BOX_IMAGE = "Images/life_bar.png";
const std::string REMAINING_LIFE = "Images/remaining_life.png";
//PAUSE & END
const std::string PAUSE_BGND_HILL_IMAGE = "Images/pause_bg_hill.png";
const std::string PAUSE_BGND_PLAIN_IMAGE = "Images/pause_bg_plain.png";
const std::string GAME_BUTTONS_IMAGE = "Images/pause_elements.png";
const std::string GRECT_BUTTON_IMAGE = "Images/rect_buttons.png";
const std::string END_BGND_IMAGE = "Images/end_background.png";

const int TRANSITION_SPEED = 10;

/********************************************
    GameView Class
*********************************************
    @author Arthur  @date 21/02 - 30/04
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
	void handleZonesTransition();


private:
    //=== ATTRIBUTES
    GameModel *m_gameModel;
    Pixelate *m_pixelShader;

    float m_xPixelIntensity;
    float m_yPixelIntensity;
    sf::Clock clock;

    //Game Textures
    sf::Texture m_farBackgroundTexture;
    sf::Texture m_farBgTransitionTexture;
    sf::Texture m_nearBackgroundTexture;
    sf::Texture m_bottomBarTexture;
    sf::Texture m_lifeBoxTexture;
    sf::Texture m_remainingLifeTexture;
    sf::Texture m_playerTexture;
    sf::Texture m_enemyTexture;
    sf::Texture m_bonusTexture;
    //Pause and End Textures
    sf::Texture m_gameButtonsTexture;
    sf::Texture m_gameRectButtonTexture;
    sf::Texture m_distanceIconTexture;
    sf::Texture m_pauseBackgroundTexture;
    sf::Texture m_endBackgroundTexture;

    //Game Graphic Elements
    SlidingBackground *m_farSlBackground;
    GraphicElement *m_farBgTransitionSprite;
    SlidingBackground *m_nearSlBackground;
    GraphicElement *m_bottomBarSprite;
    GraphicElement *m_lifeBoxSprite;
    GraphicElement *m_remainingLifeSprite;
    AnimatedGraphicElement *m_playerAnimSprite;
    AnimatedGraphicElement *m_stdEnemyAnimSprite;
    AnimatedGraphicElement *m_totemEnemyAnimSprite;
    AnimatedGraphicElement *m_blockEnemyAnimSprite;
    AnimatedGraphicElement *m_coinAnimSprite;
    AnimatedGraphicElement *m_PVPlusBonusAnimSprite;
    AnimatedGraphicElement *m_megaBonusAnimSprite;
    AnimatedGraphicElement *m_flyBonusAnimSprite;
    AnimatedGraphicElement *m_slowSpeedBonusAnimSprite;
    //Pause and End Graphic Elements
    GraphicElement *m_pauseBackgroundSprite;
    GraphicElement *m_distanceIconSprite;
    GraphicElement *m_endBackgroundSprite;
    Button *m_resumeGameButton;
    Button *m_restartGameButton;
    Button *m_goToHomeButton;
    Button *m_saveScoreButton;

    //Containers
    std::map<MovableElement*, GraphicElement*> m_MovableToGraphicElementMap;
};


#endif // GAMEVIEW_H
