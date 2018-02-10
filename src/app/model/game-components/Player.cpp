#include "Player.h"

/**
 * Constructs a player with
 * coordinates, a size, a moving vector
 * @author Arthur, Florian
 * @date 22/02/16 - 15/04/16
 *
 * @param x the x position
 * @param y the y position
 * @param w the width
 * @param h the height
 * @param mvX the x moving direction
 * @param mvY the y moving direction
 */
Player::Player(float x, float y, float w, float h, float mvX, float mvY):
    MovableElement(x, y, w, h, mvX, mvY), m_state{NORMAL}, m_gravitation{20.0},
    m_acceleration{18.0}, m_isJumping{false}, m_isFlying{false}, m_isDecelerating{false}
{
    m_elementType = PLAYER;
    m_life  = MAX_LIFE;
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

void Player::setJumpState(bool state) {  m_isJumping = state; }
void Player::setDecelerationState(bool state) {  m_isDecelerating = state; }
void Player::setLife(int new_life)
{
    m_life = new_life;
    if (m_life > MAX_LIFE) m_life = MAX_LIFE;
    else if (m_life < 0) m_life = 0;
}


/**
 * Player Moving
 * @author Florian
 * @date  12/03/16 - 15/04/16
 */
void Player::move()
{
    m_isFlying = m_width < GAME_FLOOR;

    if (m_posY < JUMP_LIMIT)
        m_isJumping = false;

    if (m_isDecelerating)
    {
        if (fabs(m_vectorBall.first) < PRECISION)
        {
            m_vectorBall.first = 0;
            m_isDecelerating = false;
        }
        m_vectorBall.first /= 1 + m_moveX/PLAYER_RATE;
    }

    if (m_isJumping && m_posY >= GAME_FLOOR)
    {
        m_vectorBall.second = -m_acceleration*m_gravitation/PLAYER_RATE;
        m_posY += m_vectorBall.second/PLAYER_RATE;
    }

    if (m_isFlying)
    {
        m_vectorBall.second += m_gravitation/PLAYER_RATE;
        m_posY += m_vectorBall.second/PLAYER_RATE;
    }

    if (m_posY == GAME_FLOOR && m_isFlying)
    {
        m_isFlying = false;
        m_isJumping = false;
        m_posY = GAME_FLOOR;
    }
    if (m_posY > GAME_FLOOR)
    {
        m_vectorBall.second = 0;
        m_posY = GAME_FLOOR;
    }

   //=== Update player position

    if (m_posX + m_vectorBall.first >= 0 && (m_posX + m_width + m_vectorBall.first) <= 900)
        m_posX += m_vectorBall.first;
    else if (m_posX + m_vectorBall.first < 0)
        m_posX = 0;
    else
        m_posX = 900 - m_width;

    if (m_posY - m_height <= 0)
       m_vectorBall.second = 0;

    m_posY += m_vectorBall.second;

    if (m_posY >= GAME_FLOOR + PRECISION)
    {
        m_vectorBall.second = 0;
        m_posY = GAME_FLOOR;
    }
}


/**
 * Changes player's state
 *
 * @param state the player's new state
 *
 * @author Arthur
 * @date  11/04/16 - 04/02/18
 */
void Player::changeState(PlayerState state)
{
    m_state = state;

    if (state == NORMAL)
    {
        m_width = 30;
        m_height = 30;
        m_gravitation = 20.0;
        m_acceleration = 18.0;
    }
    else if (state == MEGA)
    {
        m_width = 70;
        m_height = 70;
        m_gravitation = 20.0;
        m_acceleration = 18.0;
    }
    else if (state == FLYING)
    {
        m_width = 30;
        m_height = 30;
        m_gravitation = 5.0;
        m_acceleration = 70.0;
    }
    else if (state == SHIELDED || state == HARD_SHIELDED)
    {
        m_width = 30;
        m_height = 30;
        m_gravitation = 20.0;
        m_acceleration = 18.0;
    }
}

/**
 * Player's control Function
 * Arthur, Florian
 * @date  22/03/16 - 30/01/17
 *
 * @param direction the new direction
 */
void Player::controlPlayerMovements(MovingDirection direction)
{
    m_isDecelerating = false;

    if (direction == MOVE_LEFT && m_vectorBall.first > -10)
        m_vectorBall.first -= m_moveX * m_acceleration / PLAYER_RATE;
    else if (direction == MOVE_RIGHT && m_vectorBall.first < 10)
        m_vectorBall.first += m_moveX * m_acceleration / PLAYER_RATE;
}

