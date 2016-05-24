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

#include "PixelateEffect.h"
#include "View.h"

#define KEYBOARD_LEFT    (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) \
                       || sf::Keyboard::isKeyPressed(sf::Keyboard::Left ) )
#define KEYBOARD_RIGHT  (sf::Keyboard::isKeyPressed(sf::Keyboard::D) \
                       || sf::Keyboard::isKeyPressed(sf::Keyboard::Right ) )
#define KEYBOARD_JUMP  (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) \
                       || sf::Keyboard::isKeyPressed(sf::Keyboard::Space ) )

#define MOVE_LEFT true
#define MOVE_RIGHT false

/********************************************
    Constant Variables
********************************************/
//GAME
const std::string BALL_IMAGE = "Images/ball.png";
const std::string ENEMIES_IMAGE = "Images/enemies.png";
const std::string SHIELD_IMAGE = "Images/shield.png";
const std::string BOTTOM_BAR_IMAGE = "Images/bottom_bar.png";
const std::string LIFE_BOX_IMAGE = "Images/life_bar.png";
const std::string REMAINING_LIFE = "Images/remaining_life.png";
//PAUSE & END
const std::string PAUSE_BGND_HILL_IMAGE = "Images/pause_bg_hill.png";
const std::string PAUSE_BGND_PLAIN_IMAGE = "Images/pause_bg_plain.png";
const std::string GAME_BUTTONS_IMAGE = "Images/pause_elements.png";
const std::string GRECT_BUTTON_IMAGE = "Images/rect_buttons.png";
const std::string END_BGND_IMAGE = "Images/end_background.png";
//MUSIC
const std::string GAME_NORMAL_THEME_MUSIC = "Music/game_normal_sound.ogg";
const std::string GAME_MASTER_THEME_MUSIC = "Music/game_master_sound.ogg";
const std::string COINS_COLLECTED_MUSIC = "Music/coin_collected_sound.ogg";
const std::string ENEMIES_DESTRUCTED_MUSIC = "Music/destroyed_enemies_sound.ogg";


const int TRANSITION_SPEED = 10;
const int PAUSE_FORM_X = 30;

/********************************************
    GameView Class
*********************************************
    @author Arthur  @date 21/02 - 21/05
    @author Florian @date 21/02 - 6/05
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
    GameModel *m_gameModel; //to not delete in dtor
    PixelateEffect *m_pixelShader;

    float m_xPixelIntensity;
    float m_yPixelIntensity;
    bool m_isMusicEnabled;
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
    sf::Texture m_shieldTexture;
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
    GraphicElement *m_shieldAnimSprite;
    AnimatedGraphicElement *m_playerAnimSprite; //deleted in map array
    AnimatedGraphicElement *m_stdEnemyAnimSprite;
    AnimatedGraphicElement *m_totemEnemyAnimSprite;
    AnimatedGraphicElement *m_blockEnemyAnimSprite;
    AnimatedGraphicElement *m_coinAnimSprite;
    AnimatedGraphicElement *m_PVPlusBonusAnimSprite;
    AnimatedGraphicElement *m_megaBonusAnimSprite;
    AnimatedGraphicElement *m_flyBonusAnimSprite;
    AnimatedGraphicElement *m_slowSpeedBonusAnimSprite;
    AnimatedGraphicElement *m_shieldBonusAnimSprite;

    //Pause and End Graphic Elements
    GraphicElement *m_pauseBackgroundSprite;
    GraphicElement *m_distanceIconSprite;
    GraphicElement *m_endBackgroundSprite;
    Button *m_resumeGameButton;
    Button *m_restartGameButton;
    Button *m_goToHomeButton;
    Button *m_controlMusicButton;
    Button *m_saveScoreButton;

    //Music
    sf::Music m_gameThemeMusic;
    sf::Music m_coinMusic;
    sf::Music m_destructedEnemiesMusic;

    //Containers
    std::map<MovableElement*, GraphicElement*> m_MovableToGraphicElementMap;
};


#endif // GAMEVIEW_H