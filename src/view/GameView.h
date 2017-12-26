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
 * @date 21/02/16 - 16/04/17
 */
class GameView : public AbstractView
{
public:
    //=== CTORs / DTORs
    GameView(sf::RenderWindow *window, TextHandler *textHandler, GameModel *gameModel);
    virtual ~GameView() override;

    //=== METHODS

    //sprite loading
    virtual void loadImages() override;
    //synchronization
    void handleZonesTransition();
    virtual void linkElements();
    virtual void deleteElements();
    virtual void updateRunningGameElements();
    virtual void updatePausedGameElements();
    virtual void updateGameOverElements();
    virtual void synchronize() override;
    //drawing
    void drawRunningGame() const;
    void drawPausedGame() const;
    void drawGameOver() const;
    virtual void draw() const override;
    //events
    virtual bool handleEvents(sf::Event event) override;
    //music
    void handleMusic();

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
    GraphicElement *m_farTransitionBackground;
    GraphicElement *m_bottomBarImage;
    GraphicElement *m_lifeBoxImage;
    GraphicElement *m_remainingLifeImage;
    GraphicElement *m_shieldImage;
    Sprite *m_playerSprite;
    Sprite *m_stdEnemySprite;
    Sprite *m_totemEnemySprite;
    Sprite *m_blockEnemySprite;
    Sprite *m_coinSprite;
    Sprite *m_PVPlusBonusSprite;
    Sprite *m_megaBonusSprite;
    Sprite *m_flyBonusSprite;
    Sprite *m_slowSpeedBonusSprite;
    Sprite *m_shieldBonusSprite;

    //Pause and End Graphic Elements
    GraphicElement *m_pauseBackground;
    GraphicElement *m_distanceIcon;
    GraphicElement *m_endBackground;
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
    std::map<MovableElementType , Sprite*> m_typeToSpriteMap;
    std::map<MovableElement*, Sprite*> m_movableElementToSpriteMap;
};

#endif
