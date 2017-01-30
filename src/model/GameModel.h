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

#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include "AbstractModel.h"
#include "Player.h"
#include "Enemy.h"
#include "Coin.h"
#include "Bonus.h"
#include "../enum/GameState.h"
#include "../enum/Zone.h"
#include <chrono>

#define ELEMENT_MOVE_X getGameSpeed()*(-1)


/**
 * The GameModel class handles the game's logic
 * by handling MovableElements creation, behaviours,
 * and deletion, handling game mode changing,
 * handling events like zone changing,
 * calculating final score, etc.
 *
 * @author Arthur
 * @date 26/03/16 - 30/01/17
 */
class GameModel : public AbstractModel
{
public:
    //=== CTORs / DTORs
    GameModel(float width, float height, DataBase *dataBase);
    ~GameModel();

    //=== GETTERS
    GameState getGameState() const;
    bool getTransitionStatus() const;
    bool getTransitionPossibleStatus() const;
    Player* getPlayer() const;
    float getGameSpeed() const;
    Zone getCurrentZone() const;
    const std::set<MovableElement*>& getNewMElementsArray() const;
    int getBonusTimeout() const;

    //=== SETTERS
    void setGameState(GameState state);
    void setTransitionStatus(bool status);
    void setTransitionPossibleStatus(bool status);
    void setCurrentZone(Zone z);

    //=== METHODS
    virtual void nextStep() override;
    void chooseTimeSpacing(int elementType);
    bool checkIfPositionFree(float x, float y) const;
    void moveMovableElement(MovableElement *element);
    void handleMovableElementsCreation();
    void handleMovableElementsCollisions();
    void handleMovableElementsDeletion();
    void addANewMovableElement(float posX, float posY, int type);
    void clearNewMovableElementList();

private:
    //=== ATTRIBUTES
    float m_width, m_height;
    GameState m_gameState;
    bool m_inTransition;
    bool m_isTransitionPossible;
    float m_gameSpeed;
    float m_gameSlowSpeed;
    Zone m_currentZone;
    int m_currentEnemyTimeSpacing;
    int m_currentCoinTimeSpacing;
    int m_currentBonusTimeSpacing;
    int m_chosenEnemyTimeSpacing;
    int m_chosenCoinTimeSpacing;
    int m_chosenBonusTimeSpacing;
    std::chrono::system_clock::time_point m_lastTime;
    std::chrono::milliseconds m_bonusTimeout;
    Player *m_player;

    //Containers
    std::set<MovableElement*> m_movableElementsArray;
    std::set<MovableElement*> m_newMovableElementsArray;

    //Constant Variables
    const int DEFAULT_PLAYER_X = 50;
    const int ELEMENT_MOVE_Y = 0;
    const int SPEED_LIMIT = 20;
    const int NEXT_STEP_DELAY = 100;
    const int ZONE_CHANGING_DISTANCE = 500;
    const int BONUS_ROW = GAME_FLOOR-100;
    const int SHIELD_TIMEOUT = -581374;
    const float DEFAULT_SPEED = 5.0;
    const float SPEED_STEP = 0.02;
};

#endif