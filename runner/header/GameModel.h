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

#ifndef _GAMEMODEL_H
#define _GAMEMODEL_H

#include "Model.h"
#include "Player.h"
#include "Enemy.h"
#include "Coin.h"
#include "Bonus.h"
#include "Leaderboard.h"


/********************************************
    GameModel Class
*********************************************
    @author Arthur  @date 26/03 - 27/04
*********************************************/
class GameModel : public Model
{
public:
    //=== CTORs / DTORs
    GameModel(const Model& model);
    ~GameModel();

    //=== GETTERS
    bool getPauseState() const;
    bool getEndState() const;
    bool getTransitionStatus() const;
    bool getTransitionPossibleStatus() const;
    bool getScoreSavableStatus() const;
    Player* getPlayer() const;
    int getScore() const;
    int getDistance() const;
    float getGameSpeed() const;
    int getCurrentZone() const;
    unsigned int getNbCoinsCollected() const;
    unsigned int getEnemyDestructedBonus() const;
    const std::set<MovableElement*>& getNewMElementsArray() const;
    int getBonusTimeout() const;

    //=== SETTERS
    void setPauseState(bool state);
    void setEndState(bool state);
    void setTransitionStatus(bool status);
    void setTransitionPossibleStatus(bool status);
    void setScoreSavableStatus(bool status);
    void setCurrentZone(int number);
    void setNbCoinsCollected(unsigned int number) ;

    //=== METHODS
    virtual void nextStep() override;
    void chooseInterdistance(int elementType);
    bool checkIfPositionFree(float x, float y) const;
    void moveBallAccordingEvent(bool left);
    void moveMovableElement(MovableElement *element);
    void handleMovableElementsCreation();
    void handleMovableElementsCollisions();
    void handleMovableElementsDeletion();
    void addANewMovableElement(float posX, float posY, int type);
    void clearNewMovableElementList();

private:
    //=== ATTRIBUTES
    bool m_pauseState;
    bool m_endState;
    bool m_inTransition;
    bool m_isTransitionPossible;
    bool m_isScoreSavable;
    int m_score;
    int m_distance;
    float m_gameSpeed;
    float m_realGameSpeed;
    int m_currentZone;
    int m_nbCoinsCollected;
    int m_enemyDestructedBonus;
    int m_activeBonusType; /**< nope : -1, mega : 0, fly : 1  */
    int m_currentEnemyInterdistance;
    int m_currentCoinInterdistance;
    int m_currentBonusInterdistance;
    int m_chosenEnemyInterdistance;
    int m_chosenCoinInterdistance;
    int m_chosenBonusInterdistance;
    std::chrono::system_clock::time_point m_lastTime;
    std::chrono::system_clock::time_point m_bonusStopTime;
    std::chrono::milliseconds m_bonusTimeout;

    Player *m_player;
    MovableElement *m_newMElement;

    //Containers
    std::set<MovableElement*> m_movableElementsArray;
    std::set<MovableElement*> m_newMovableElementsArray;

};

#endif
