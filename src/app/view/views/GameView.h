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

#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include "libs/MDC-SFML/src/RaisedButton.h"
#include "app/model/models/GameModel.h"
#include "app/view/ui-components/PixelShader.h"
#include "AbstractView.h"
#include "app/view/ui-components/ParallaxBackground.h"

/**
 * @class GameView
 *
 * @author Arthur, Florian
 * @date 21/02/16 - 13/07/2019
 */
class GameView: public AbstractView
{
public:
    //=== CTORs / DTORs
    GameView(sf::RenderWindow* window, AppTextManager* textManager, GameModel* gameModel);
    ~GameView() override;

    //=== METHODS
    void synchronize() override;
    void draw() const override;
    bool handleEvents(sf::Event& event) override;

private:
    //=== ATTRIBUTES
    GameModel* m_game;
    PixelShader* m_pixelShader;
    float m_xPixelIntensity;
    float m_yPixelIntensity;

    //Constants
    const unsigned int SCROLLING_BACKGROUND = 0;
    const unsigned int SCROLLING_FOREGROUND = 1;
    const int TRANSITION_SPEED = 10;
    const int PAUSE_FORM_X = 30;
    const int HOME_BTN_SIZE = 30;
    const int PAUSE_BUTTONS_SIZE = 25;
    const int INGAME_COIN_SIZE = 20;
    const int RESULTS_COIN_SIZE = 25;
    const int BUTTON_WIDTH = 150;
    const int BUTTON_HEIGHT = 40;
    const int ENEMY_SIZE = 20;
    const int SHIELD_SIZE = 40;
    const int ORIGINAL_DISTANCE_ICON_SIZE = 50;
    const int PAUSE_ICONS_SIZE = 25;
    const int NB_PLAYER_CLIPS = 8;
    const int LIFE_BOX_WIDTH = 200;
    const int LIFE_BOX_HEIGHT = 100;
    const int LIFE_LEVEL_WIDTH = 300;
    const int LIFE_LEVEL_HEIGHT = 50;
    static constexpr float INITIAL_PIXEL_INTENSITY = 1;

    //Game Graphic Elements
    ParallaxBackground* m_parallaxBackground;
    mdsf::Sprite* m_farTransitionBackground;
    mdsf::Sprite* m_bottomBarImage;
    mdsf::Sprite* m_lifeBoxImage;
    mdsf::Sprite* m_remainingLifeImage;
    mdsf::Sprite* m_shieldImage;
    AnimatedSprite* m_playerSprite;
    AnimatedSprite* m_stdEnemySprite;
    AnimatedSprite* m_totemEnemySprite;
    AnimatedSprite* m_blockEnemySprite;
    AnimatedSprite* m_coinSprite;
    AnimatedSprite* m_PVPlusBonusSprite;
    AnimatedSprite* m_megaBonusSprite;
    AnimatedSprite* m_flyBonusSprite;
    AnimatedSprite* m_slowSpeedBonusSprite;
    AnimatedSprite* m_shieldBonusSprite;

    //Pause and End Graphic Elements
    mdsf::Sprite* m_pauseBackground;
    mdsf::Sprite* m_distanceIcon;
    mdsf::Sprite* m_endBackground;
    mdsf::Button* m_resumeGameButton;
    mdsf::Button* m_restartGameButton;
    mdsf::Button* m_goToHomeButton;
    mdsf::Button* m_controlMusicButton;
    mdsf::RaisedButton* m_saveScoreButton;

    //Audio
    sf::Music m_gameThemeMusic;
    sf::Music m_coinMusic;
    sf::Music m_destructedEnemiesMusic;

    //Containers
    std::map<MovableElementType, AnimatedSprite*> m_typeToSpriteMap;
    std::map<MovableElement*, AnimatedSprite*> m_movableElementToSpriteMap;

    //=== METHODS

    //Sprite loading
    void loadSprites() override;

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

    //Audio
    void handleMusic();

    //Events
    void handlePlayerInput() const;
    bool handleRunningGameEvents(const sf::Event& event);
    bool handlePausedGameEvents(const sf::Event& event);
    bool handleGameOverEvents(const sf::Event& event);
};

#endif
