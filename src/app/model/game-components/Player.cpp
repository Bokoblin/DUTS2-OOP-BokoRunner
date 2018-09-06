#include "Player.h"

/**
 * Constructs a player with
 * coordinates, a size, a moving vector
 * @author Arthur, Florian
 * @date 22/02/16 - 05/09/18
 *
 * @param x the x position
 * @param y the y position
 * @param w the width
 * @param h the height
 * @param mvX the x moving direction
 * @param mvY the y moving direction
 * @param floor the floor y position
 * @param fieldWidth the total field width
 */
Player::Player(float x, float y, float w, float h, float mvX, float mvY, const int floor, const int fieldWidth) :
        MovableElement(x, y, w, h, mvX, mvY), m_state{NORMAL}, m_life{MAX_LIFE}, m_initialWidth{w}, m_initialHeight{h},
        m_floor_position{floor}, m_fieldWidth{fieldWidth}, m_gravitation{INITIAL_GRAVITATION},
        m_acceleration{INITIAL_ACCELERATION}, m_isJumping{false}, m_isFlying{false}, m_isDecelerating{false}
{
    m_elementType = PLAYER;
    m_life = MAX_LIFE;
    m_vectorBall.first = 0;
    m_vectorBall.second = 0;
}

/**
 * Destructor
 * @author Arthur, Florian
 * @date 22/02/16
 */
Player::~Player() = default;


//=== Getters

PlayerState Player::getState() const { return m_state; }
int Player::getLife() const { return m_life; }


//=== Setters

void Player::setJumpState(bool state) { m_isJumping = state; }
void Player::setDecelerationState(bool state) { m_isDecelerating = state; }
void Player::setLife(int new_life)
{
    m_life = new_life;
    if (m_life > MAX_LIFE) {
        m_life = MAX_LIFE;
    } else if (m_life < MIN_LIFE) {
        m_life = MIN_LIFE;
    }
}


/**
 * Player Moving
 * @author Florian
 * @date  12/03/16 - 05/09/18
 */
void Player::move()
{
    m_isFlying = m_width < m_floor_position;

    if (m_posY < JUMP_LIMIT) {
        m_isJumping = false;
    }

    if (m_isDecelerating) {
        if (fabs(m_vectorBall.first) < PRECISION) {
            m_vectorBall.first = 0;
            m_isDecelerating = false;
        }
        m_vectorBall.first /= 1 + m_moveX / PLAYER_RATE;
    }

    if (m_isJumping && m_posY >= m_floor_position) {
        m_vectorBall.second = -m_acceleration * m_gravitation / PLAYER_RATE;
        m_posY += m_vectorBall.second / PLAYER_RATE;
    }

    if (m_isFlying) {
        m_vectorBall.second += m_gravitation / PLAYER_RATE;
        m_posY += m_vectorBall.second / PLAYER_RATE;
    }

    if (m_posY == m_floor_position && m_isFlying) {
        m_isFlying = false;
        m_isJumping = false;
        m_posY = m_floor_position;
    }
    if (m_posY > m_floor_position) {
        m_vectorBall.second = 0;
        m_posY = m_floor_position;
    }

    //=== Update player position

    if (m_posX + m_vectorBall.first >= 0 && (m_posX + m_width + m_vectorBall.first) <= m_fieldWidth) {
        m_posX += m_vectorBall.first;
    } else if (m_posX + m_vectorBall.first < 0) {
        m_posX = 0;
    } else {
        m_posX = m_fieldWidth - m_width;
    }

    if (m_posY - m_height <= 0) {
        m_vectorBall.second = 0;
    }

    m_posY += m_vectorBall.second;

    if (m_posY >= m_floor_position + PRECISION) {
        m_vectorBall.second = 0;
        m_posY = m_floor_position;
    }
}


/**
 * Changes player's state
 *
 * @param state the player's new state
 *
 * @author Arthur
 * @date  11/04/16 - 05/09/18
 */
void Player::changeState(PlayerState state)
{
    m_state = state;

    if (state == NORMAL) {
        m_width = m_initialWidth;
        m_height = m_initialHeight;
        m_gravitation = INITIAL_GRAVITATION;
        m_acceleration = INITIAL_ACCELERATION;
    } else if (state == MEGA) {
        m_width = m_initialWidth * 2;
        m_height = m_initialHeight * 2;
        m_gravitation = INITIAL_GRAVITATION;
        m_acceleration = INITIAL_ACCELERATION;
    } else if (state == FLYING) {
        m_width = m_initialWidth;
        m_height = m_initialHeight;
        m_gravitation = 5.0;
        m_acceleration = 70.0;
    } else if (state == SHIELDED || state == HARD_SHIELDED) {
        m_width = m_initialWidth;
        m_height = m_initialHeight;
        m_gravitation = INITIAL_GRAVITATION;
        m_acceleration = INITIAL_ACCELERATION;
    }
}

/**
 * Player's control Function
 * Arthur, Florian
 * @date  22/03/16 - 05/09/18
 *
 * @param direction the new direction
 */
void Player::controlPlayerMovements(MovingDirection direction)
{
    m_isDecelerating = false;

    if (direction == MOVE_LEFT && m_vectorBall.first > -1 * DIRECTION_PADDING) {
        m_vectorBall.first -= m_moveX * m_acceleration / PLAYER_RATE;
    } else if (direction == MOVE_RIGHT && m_vectorBall.first < DIRECTION_PADDING) {
        m_vectorBall.first += m_moveX * m_acceleration / PLAYER_RATE;
    }
}

