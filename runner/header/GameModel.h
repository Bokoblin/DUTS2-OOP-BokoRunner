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

#define DEFAULT_SPEED 5.0
#define SHIELD_TIMEOUT -581374

/********************************************
    GameModel Class
*********************************************
    @author Arthur  @date 26/03 - 21/05
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
    bool getSaveStatus() const;
    Player* getPlayer() const;
    float getGameSpeed() const;
    int getCurrentZone() const;
    const std::set<MovableElement*>& getNewMElementsArray() const;
    int getBonusTimeout() const;

    //=== SETTERS
    void setPauseState(bool state);
    void setEndState(bool state);
    void setTransitionStatus(bool status);
    void setTransitionPossibleStatus(bool status);
    void setSaveStatus(bool status);
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
    bool m_isSavePossible;
    float m_gameSpeed;
    int m_currentZone;
    int m_currentEnemyInterdistance;
    int m_currentCoinInterdistance;
    int m_currentBonusInterdistance;
    int m_chosenEnemyInterdistance;
    int m_chosenCoinInterdistance;
    int m_chosenBonusInterdistance;
    std::chrono::system_clock::time_point m_lastTime;
    std::chrono::milliseconds m_bonusTimeout;
    Player *m_player;

    //Containers
    std::set<MovableElement*> m_movableElementsArray;
    std::set<MovableElement*> m_newMovableElementsArray;
};

#endif
