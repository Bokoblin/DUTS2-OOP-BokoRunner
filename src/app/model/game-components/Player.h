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

#ifndef PLAYER_H
#define PLAYER_H

#include "MovableElement.h"
#include "app/model/enums/MovingDirection.h"
#include "app/model/enums/PlayerState.h"
#include "app/model/core/ModelConstants.h"
#include <cmath>
#include <utility>

/**
 * @class Player
 * @inherit MovableElement
 * @details Provide player's logic and behaviours
 *
 * @author Arthur, Florian
 * @date 22/02/2016 - 13/01/2019
 */
class Player: public MovableElement
{
public:
    //=== CTORs / DTORs
    Player(float x, float y, float w, float h, float mvX, float mvY, int floor, int fieldWidth, int jumpLimit);
    ~Player() override;

    //=== GETTERS
    PlayerState getState() const;
    int getLife() const;

    //=== METHODS
    void move() override;
    void takeDamages(int amount);
    void heal(int energy);
    void jump();
    void decelerate();
    void changeState(const PlayerState& state);
    void controlPlayerMovements(const MovingDirection& direction);

    //=== CONSTANTS
    static constexpr int MIN_ENERGY = 0;

private:
    //=== ATTRIBUTES
    PlayerState m_state;
    int m_energy;
    float m_initialWidth;
    float m_initialHeight;
    int m_floorPosition;
    int m_fieldWidth;
    int m_jumpLimit;
    float m_gravitation;
    float m_acceleration;
    bool m_isJumping;
    bool m_isFlying;
    bool m_isDecelerating;
    std::pair<float, float> m_playerVector;

    //Constants
    static constexpr int MAX_ENERGY = 100;
    static constexpr int PLAYER_RATE = 30;
    static constexpr int DIRECTION_PADDING = 10;
    static constexpr float PRECISION = 1.0;
    static constexpr float INITIAL_GRAVITATION = 20.0;
    static constexpr float FLYING_GRAVITATION = 5.0;
    static constexpr float INITIAL_ACCELERATION = 18.0;
    static constexpr float FLYING_ACCELERATION = 70.0;
};

#endif
