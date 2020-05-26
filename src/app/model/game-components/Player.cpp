#include "Player.h"

constexpr int Player::MAX_ENERGY;

//------------------------------------------------
//          CONSTRUCTOR / DESTRUCTOR
//------------------------------------------------

/**
 * @brief Constructor
 *
 * @param x the x position
 * @param y the y position
 * @param w the width
 * @param h the height
 * @param mvX the x moving direction
 * @param mvY the y moving direction
 * @param floor the floor y position
 * @param fieldWidth the total field width
 * @param jumpLimit the jump limit in height
 *
 * @author Arthur, Florian
 * @date 22/02/2016 - 16/09/2018
 */
Player::Player(float x, float y, float w, float h, float mvX, float mvY, int floor, int fieldWidth, int jumpLimit) :
        MovableElement(x, y, w, h, mvX, mvY), m_state{NORMAL}, m_energy{MAX_ENERGY}, m_initialWidth{w}, m_initialHeight{h},
        m_floorPosition{floor}, m_fieldWidth{fieldWidth}, m_jumpLimit{jumpLimit}, m_gravitation{INITIAL_GRAVITATION},
        m_acceleration{INITIAL_ACCELERATION}, m_isJumping{false}, m_isFlying{false}, m_isDecelerating{false}
{
    m_elementType = PLAYER;
    m_playerVector.first = 0;
    m_playerVector.second = 0;
}

/**
 * @brief Destructor
 *
 * @author Arthur, Florian
 * @date 22/02/2016
 */
Player::~Player() = default;

//------------------------------------------------
//          GETTERS
//------------------------------------------------

PlayerState Player::getState() const { return m_state; }
int Player::getLife() const { return m_energy; }


//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * @brief Execute the move routine
 *
 * @author Florian
 * @date  12/03/2016 - 16/09/2018
 */
void Player::move()
{
    m_isFlying = m_width < m_floorPosition;

    if (m_posY < m_jumpLimit) {
        m_isJumping = false;
    }

    if (m_isDecelerating) {
        if (fabs(m_playerVector.first) < PRECISION) {
            m_playerVector.first = 0;
            m_isDecelerating = false;
        }
        m_playerVector.first /= 1 + m_moveX / PLAYER_RATE;
    }

    if (m_isJumping && m_posY >= m_floorPosition) {
        m_playerVector.second = -m_acceleration * m_gravitation / PLAYER_RATE;
        m_posY += m_playerVector.second / PLAYER_RATE;
    }

    if (m_isFlying) {
        m_playerVector.second += m_gravitation / PLAYER_RATE;
        m_posY += m_playerVector.second / PLAYER_RATE;
    }

    if (m_posY == m_floorPosition && m_isFlying) {
        m_isFlying = false;
        m_isJumping = false;
        m_posY = m_floorPosition;
    }
    if (m_posY > m_floorPosition) {
        m_playerVector.second = 0;
        m_posY = m_floorPosition;
    }

    //=== Update player position

    if (m_posX + m_playerVector.first >= 0 && (m_posX + m_width + m_playerVector.first) <= m_fieldWidth) {
        m_posX += m_playerVector.first;
    } else if (m_posX + m_playerVector.first < 0) {
        m_posX = 0;
    } else {
        m_posX = m_fieldWidth - m_width;
    }

    if (m_posY - m_height <= 0) {
        m_playerVector.second = 0;
    }

    m_posY += m_playerVector.second;

    if (m_posY >= m_floorPosition + PRECISION) {
        m_playerVector.second = 0;
        m_posY = m_floorPosition;
    }
}

/**
 * @brief Take damages by reducing energy
 *
 * @param amount the amount to remove
 *
 * @author Arthur
 * @date  13/01/2019
 */
void Player::takeDamages(int amount)
{
    m_energy = std::max(0, m_energy - amount);
}

/**
 * @brief Restore some energy to the player
 *
 * @param energy the energy to add
 *
 * @author Arthur
 * @date  13/01/2019
 */
void Player::heal(int energy)
{
    m_energy = std::min(MAX_ENERGY, m_energy + energy);
}

/**
 * @brief Allows the player to jump
 *
 * @author Arthur
 * @date  13/01/2019
 */
void Player::jump()
{
    m_isJumping = true;
}

/**
 * @brief Allows the player to decelerate
 *
 * @date  13/01/2019
 */
void Player::decelerate()
{
    m_isDecelerating = true;
}

/**
 * @brief Change player's state
 *
 * @param state the player's new state
 *
 * @date  11/04/2016 - 05/09/2018
 */
void Player::changeState(const PlayerState& state)
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
        m_gravitation = FLYING_GRAVITATION;
        m_acceleration = FLYING_ACCELERATION;
    } else if (state == SHIELDED || state == HARD_SHIELDED) {
        m_width = m_initialWidth;
        m_height = m_initialHeight;
        m_gravitation = INITIAL_GRAVITATION;
        m_acceleration = INITIAL_ACCELERATION;
    }
}

/**
 * @brief Player's control Function
 *
 * @param direction the new direction
 *
 * @author Arthur, Florian
 * @date  22/03/2016 - 05/09/2018
 */
void Player::controlPlayerMovements(const MovingDirection& direction)
{
    m_isDecelerating = false;

    if (direction == MOVE_LEFT && m_playerVector.first > -1 * DIRECTION_PADDING) {
        m_playerVector.first -= m_moveX * m_acceleration / PLAYER_RATE;
    } else if (direction == MOVE_RIGHT && m_playerVector.first < DIRECTION_PADDING) {
        m_playerVector.first += m_moveX * m_acceleration / PLAYER_RATE;
    }
}
