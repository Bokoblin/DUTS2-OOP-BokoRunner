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

#ifndef PLAYER_H
#define PLAYER_H

#include "MovableElement.h"
#include <cmath>
#include <utility>

const int GAME_FLOOR = 480;
const int FRAMERATE = 30;
const int JUMP_LIMIT = 380;
const float PRECISION = 1.0;

enum playerState
{
    NORMAL,
    MEGA,
    FLY,
    SHIELD
};

enum MoveDirections {
    MOVE_LEFT = true,
    MOVE_RIGHT = false
};

/**
 * Player Class
 * @author Arthur, Florian
 * @date 22/02/16 - 04/01/17
 */
class Player : public MovableElement
{
public:
    //=== CTORs / DTORs
    Player(float x, float y, float w, float h, float mvX, float mvY);
    virtual ~Player();

    //=== GETTERS
    int getState() const;
    int getLife() const;
    bool getFlyingState() const;
    bool getJumpState() const;
    bool getDecelerationState() const;
    std::pair<float,float> getVector() const;

    //=== SETTERS
    void setLife(int new_life);
    void setFlyingState(bool state);
    void setJumpState(bool state);
    void setDecelerationState(bool state);

    //=== METHODS
    virtual void move() override;
    void changeState(int state);
    void controlPlayerMovements(MoveDirections direction);


private:
    int m_state;
    int m_life;
    float m_gravitation;
    float m_acceleration;
    bool m_jumping;
    bool m_flying;
    bool m_inDeceleration;
    std::pair<float,float> m_vectorBall;
};

#endif
