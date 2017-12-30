#include "Player.h"

using namespace std;

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
    MovableElement(x, y, w, h, mvX, mvY), m_state{0}, m_gravitation{20.0},
    m_acceleration{18.0}, m_jumping{false}, m_flying{false}, m_inDeceleration{false}
{
    m_elementType = 0;
    m_life  = 100;
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

int Player::getState() const { return m_state; }
int Player::getLife() const { return m_life; }


//=== Setters

void Player::setJumping(bool state) {  m_jumping = state; }
void Player::setDeceleration(bool state) {  m_inDeceleration = state; }
void Player::setLife(int new_life)
{
    m_life = new_life;
    if ( m_life > 100 ) m_life = 100;
    else if ( m_life < 0 ) m_life = 0;
}


/**
 * Player Moving
 * @author Florian
 * @date  12/03/16 - 15/04/16
 */
void Player::move()
{
    m_flying = m_width < GAME_FLOOR;

    if (m_posY < JUMP_LIMIT)
        m_jumping = false;

    if(m_inDeceleration)
    {
        if(fabs(m_vectorBall.first) < PRECISION)
        {
            m_vectorBall.first =0;
            m_inDeceleration = false;
        }
        m_vectorBall.first /= 1+m_moveX/FRAMERATE;
    }

    if(m_jumping && m_posY >=GAME_FLOOR)
    {
        m_vectorBall.second = -m_acceleration*m_gravitation/FRAMERATE;
        m_posY+= m_vectorBall.second/FRAMERATE;
    }

    if(m_flying)
    {
        m_vectorBall.second += m_gravitation/FRAMERATE;
        m_posY+= m_vectorBall.second/FRAMERATE;
    }

    if( m_posY == GAME_FLOOR && m_flying)
    {
        m_flying =false;
        m_jumping=false;
        m_posY = GAME_FLOOR;
    }
    if(m_posY > GAME_FLOOR )
    {
        m_vectorBall.second = 0;
        m_posY = GAME_FLOOR;
    }

   //=== Update player position

    if ( m_posX + m_vectorBall.first >= 0 && (m_posX + m_width + m_vectorBall.first) <= 900 )
        m_posX += m_vectorBall.first;
    else if (m_posX + m_vectorBall.first < 0)
        m_posX = 0;
    else
        m_posX = 900 - m_width;

    if(m_posY - m_height <= 0)
       m_vectorBall.second =0;

    m_posY += m_vectorBall.second;

    if(m_posY >= GAME_FLOOR + PRECISION)
    {
        m_vectorBall.second =0;
        m_posY=GAME_FLOOR;
    }
}


/**
 * Changes player's state
 * @author Arthur
 * @date  11/04/16 - 21/05/16
 *
 * @param state the player's new state
 */
void Player::changeState(int state)
{
    if ( state == NORMAL)
    {
        m_state = NORMAL;
        m_width = 30;
        m_height = 30;
        m_gravitation = 20.0;
        m_acceleration = 18.0;
    }
    else if ( state == MEGA)
    {
        m_state = MEGA;
        m_width = 70;
        m_height = 70;
        m_gravitation = 20.0;
        m_acceleration = 18.0;
    }
    else if ( state == FLY)
    {
        m_state = FLY;
        m_width = 30;
        m_height = 30;
        m_gravitation = 5.0;
        m_acceleration = 70.0;
    }
    else if ( state == SHIELD)
    {
        m_state = SHIELD;
        m_width = 30;
        m_height = 30;
        m_gravitation = 20.0;
        m_acceleration = 18.0;
    }
    else
        m_state = state;
}

/**
 * Player's control Function
 * Arthur, Florian
 * @date  22/03/16 - 04/01/17
 *
 * @param direction the new direction
 */
void Player::controlPlayerMovements(MoveDirections direction)
{
    m_inDeceleration = false;

    if (direction && m_vectorBall.first > -10)
        m_vectorBall.first -= m_moveX*m_acceleration/FRAMERATE;
    else if (!direction && m_vectorBall.first < 10)
        m_vectorBall.first += m_moveX*m_acceleration/FRAMERATE;
}

