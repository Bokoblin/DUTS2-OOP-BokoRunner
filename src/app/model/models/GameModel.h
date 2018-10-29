/* Copyright 2016-2018 Jolivet Arthur & Laronze Florian

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

#include <chrono>
#include "app/model/enums/GameState.h"
#include "app/model/enums/Zone.h"
#include "app/model/game-components/Bonus.h"
#include "app/model/game-components/Coin.h"
#include "app/model/game-components/Enemy.h"
#include "app/model/game-components/Player.h"
#include "AbstractModel.h"

/**
 * The GameModel class handles the game's logic
 * by handling MovableElements creation, behaviours,
 * and deletion, handling game mode changing,
 * handling events like zone changing,
 * calculating final score, etc.
 *
 * @author Arthur
 * @date 26/03/16 - 30/10/18
 */
class GameModel: public AbstractModel
{
public:
    //=== CTORs / DTORs
    GameModel(float width, float height, AppCore* appCore);
    ~GameModel() override;

    //=== GETTERS
    GameState getGameState() const;
    int getGameDifficulty() const;
    const std::string getPlayerSkin() const;
    Player* getPlayer() const;
    float getGameSpeed() const;
    Zone getCurrentZone() const;
    const std::set<MovableElement*>& getNewMElementsArray() const;
    int getBonusTimeout() const;
    unsigned int getGameFloorPosition() const;
    bool isTransitionRunning() const;
    bool isTransitionPossible() const;
    bool isMusicEnabled() const;

    //=== SETTERS
    void setGameState(GameState state);
    void setTransitionState(bool inTransition);
    void setCurrentZone(Zone z);
    void disableTransitionPossibility();
    void toggleGameMusic();

    //=== METHODS
    void nextStep() override;
    void moveMovableElement(MovableElement* element);
    void clearNewMovableElementList();
    void saveCurrentGame();

private:
    //=== ATTRIBUTES
    float m_width, m_height;
    GameState m_gameState;
    bool m_inTransition;
    bool m_isTransitionPossible;
    float m_gameSpeed;
    float m_gameSlowSpeed;
    Zone m_currentZone;
    int m_currentEnemySpawnDistance;
    int m_currentCoinSpawnDistance;
    int m_currentBonusSpawnDistance;
    int m_nextEnemySpawnDistance;
    int m_nextCoinSpawnDistance;
    int m_nextBonusSpawnDistance;
    int m_scoreBonusFlattenedEnemies;
    std::chrono::system_clock::time_point m_lastTime;
    std::chrono::milliseconds m_bonusTimeout;
    Player* m_player;

    //Containers
    std::set<MovableElement*> m_movableElementsArray;
    std::set<MovableElement*> m_newMovableElementsArray;

    //Constants
    const int DEFAULT_PLAYER_X = 50;
    const int ELEMENT_SIZE = 30;
    const int ITEM_SIZE = 25;
    const int ELEMENT_MOVE_Y = 0;
    const int SPEED_LIMIT = 20;
    const int NEXT_STEP_DELAY = 100;
    const int ZONE_CHANGING_DISTANCE = 500;
    const int MEGA_TIMEOUT = 10000;
    const int FLY_TIMEOUT = 15000;
    const int SLOW_SPEED_TIMEOUT = 20000;
    const int ADDITIONAL_TIMEOUT = 5000;
    const float DEFAULT_SPEED = 5.0;
    const float SPEED_STEP = 0.02;
    const int PV_BONUS_INCREASE = 10;
    const int SLOW_SPEED_BONUS_DIVIDER = 2;
    const int MEGA_BONUS_FLATTENED_STD = 100;
    const int MEGA_BONUS_FLATTENED_TOTEM = 300;
    const int MEGA_BONUS_FLATTENED_BLOCK = 500;
    const int COLLISION_DAMAGE_STD = 10;
    const int COLLISION_DAMAGE_TOTEM = 15;
    const int COLLISION_DAMAGE_BLOCK = 25;
    const int SPEED_DISTANCE_RATIO = 5;

    //=== PRIVATE METHODS
    void handleSpeedAndDistance();
    void handleMovableElementsCreation();
    void handleMovableElementsCollisions();
    void handleMovableElementsDeletion();
    void handleEnemyCollision(MovableElementType enemyType);
    void handleCoinCollision() const;
    void handleBonusCollision(MovableElementType bonusType);
    void handleBonusTimeout();
    void conditionallyAllowZoneTransition();
    void conditionallyTriggerGameOver();
    bool checkIfPositionFree(float x, float y) const;
    void addANewMovableElement(float posX, float posY, int type);
};

#endif
