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

#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include "PixelateEffect.h"
#include "View.h"

#define KEYBOARD_LEFT  (sf::Keyboard::isKeyPressed(sf::Keyboard::A) \
                       || sf::Keyboard::isKeyPressed(sf::Keyboard::Left ) )
#define KEYBOARD_RIGHT (sf::Keyboard::isKeyPressed(sf::Keyboard::D) \
                       || sf::Keyboard::isKeyPressed(sf::Keyboard::Right ) )
#define KEYBOARD_JUMP  (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) \
                       || sf::Keyboard::isKeyPressed(sf::Keyboard::W ) )


/**
 * GameView Class
 * @author Arthur, Florian
 * @date 21/02/16 - 10/04/17
 */
class GameView : public View
{
public:
    //=== CTORs / DTORs
    GameView(float w, float h, sf::RenderWindow *myWindow, TextHandler *text);
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
    void handleMusic();


private:
    //=== ATTRIBUTES
    GameModel *m_gameModel; //to not delete in dtor
    PixelateEffect *m_pixelShader;
    float m_xPixelIntensity;
    float m_yPixelIntensity;
    const int TRANSITION_SPEED = 10;
    const int PAUSE_FORM_X = 30;

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

    //Audio
    sf::Music m_gameThemeMusic;
    sf::Music m_coinMusic;
    sf::Music m_destructedEnemiesMusic;

    //Containers
    std::map<MovableElement*, GraphicElement*> m_MovableToGraphicElementMap;
};


#endif