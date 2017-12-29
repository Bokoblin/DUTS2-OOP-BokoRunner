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

#include "PixelShader.h"
#include "AbstractView.h"
#include "../model/GameModel.h"
#include "../utils/definitions.h"

/**
 * GameView Class
 * @author Arthur, Florian
 * @date 21/02/16 - 27/12/17
 */
class GameView : public AbstractView
{
public:
    //=== CTORs / DTORs
    GameView(sf::RenderWindow *window, TextHandler *textHandler, GameModel *gameModel);
    ~GameView() override;

    //=== METHODS
    void synchronize() override;
    void draw() const override;
    bool handleEvents(sf::Event event) override;

private:
    //=== ATTRIBUTES
    GameModel *m_game; //to not delete in dtor
    PixelShader *m_pixelShader;
    float m_xPixelIntensity;
    float m_yPixelIntensity;
    const int TRANSITION_SPEED = 10;
    const int PAUSE_FORM_X = 30;

    //Game Graphic Elements
    ScrollingBackground *m_farScrollingBackground;
    ScrollingBackground *m_nearScrollingBackground;
    mdsf::Sprite *m_farTransitionBackground;
    mdsf::Sprite *m_bottomBarImage;
    mdsf::Sprite *m_lifeBoxImage;
    mdsf::Sprite *m_remainingLifeImage;
    mdsf::Sprite *m_shieldImage;
    AnimatedSprite *m_playerSprite;
    AnimatedSprite *m_stdEnemySprite;
    AnimatedSprite *m_totemEnemySprite;
    AnimatedSprite *m_blockEnemySprite;
    AnimatedSprite *m_coinSprite;
    AnimatedSprite *m_PVPlusBonusSprite;
    AnimatedSprite *m_megaBonusSprite;
    AnimatedSprite *m_flyBonusSprite;
    AnimatedSprite *m_slowSpeedBonusSprite;
    AnimatedSprite *m_shieldBonusSprite;

    //Pause and End Graphic Elements
    mdsf::Sprite *m_pauseBackground;
    mdsf::Sprite *m_distanceIcon;
    mdsf::Sprite *m_endBackground;
    mdsf::Button *m_resumeGameButton;
    mdsf::Button *m_restartGameButton;
    mdsf::Button *m_goToHomeButton;
    mdsf::Button *m_controlMusicButton;
    mdsf::Button *m_saveScoreButton;

    //Audio
    sf::Music m_gameThemeMusic;
    sf::Music m_coinMusic;
    sf::Music m_destructedEnemiesMusic;

    //Containers
    std::map<MovableElementType , AnimatedSprite*> m_typeToSpriteMap;
    std::map<MovableElement*, AnimatedSprite*> m_movableElementToSpriteMap;

    //=== METHODS

    //Sprite loading
    void loadImages() override;

    //Zone transition
    void processZonesTransition();
    void setupTransition();

    //Synchronization
    virtual void linkElements();
    virtual void deleteElements();
    virtual void updateRunningGameElements();
    virtual void updatePausedGameElements();
    virtual void updateGameOverElements();

    //Drawing
    void drawRunningGame() const;
    void drawPausedGame() const;
    void drawGameOver() const;

    //Events
    void handlePlayerInput() const;
    bool handleRunningGameEvents(sf::Event event);
    bool handlePausedGameEvents(sf::Event event);
    bool handleGameOverEvents(sf::Event event);

    //Audio
    void handleMusic();
};

#endif
