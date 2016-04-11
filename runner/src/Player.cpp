#include "../header/Player.h"


/********************************************
    Parameterized Constructor
*********************************************
    @author Arthur  @date 22/02 - 11/04
    @author Florian @date 22/02 - 06/04
*********************************************/
Player::Player(float x, float y, float w, float h, float mvX, float mvY):
    MovableElement(x, y, w, h, mvX, mvY),
    m_jumping{false}, m_flying{false}, m_inDeceleration{false}
{
    m_elementType = 0;
    m_life  = 100;
    m_vectorBall.first = 0;
    m_vectorBall.second = 0;
}

/********************************************
    Destructor
*********************************************
    @author Arthur  @date 22/02
    @author Florian @date 22/02
*********************************************/
Player::~Player()
{}


/********************************************
    Getters
*********************************************
    @author Arthur  @date 20/03 - 9/04
    @author Florian @date 17/03 - 10/04
*********************************************/
bool Player::getFlyingState() const { return m_flying; }
bool Player::getJumpState() const { return m_jumping; }
bool Player::getDecelerationState() const { return m_inDeceleration; }
std::pair<float,float> Player::getVector() const { return m_vectorBall; }


/********************************************
    Setters
*********************************************
    @author Arthur  @date 08/04 - 09/04
    @author Florian @date 17/03 - 6/04
*********************************************/
void Player::setFlyingState(bool etat) { m_flying = etat; }
void Player::setJumpState(bool etat) {  m_jumping = etat; }
void Player::setDecelerationState(bool etat) {  m_inDeceleration = etat; }

void Player::setLife(unsigned int new_life)
{
    if ( m_life <= new_life)
        m_life = 0;
    else
        m_life = new_life;
}


/********************************************
    Player Move Function
*********************************************
    @author Arthur  @date  8/04 - 9/04
    @author Florian @date  12/03 - 10/04
*********************************************/
void Player::move()
{
    m_flying =m_width < GAME_FLOOR;

    if (m_posY < JUMP_LIMIT)
        m_jumping = false;

    if(m_inDeceleration == true)
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
        m_vectorBall.second = -m_moveY*GRAVITATION/FRAMERATE;
        m_posY+= m_vectorBall.second/FRAMERATE;
    }

    if(m_flying)
    {
        m_vectorBall.second += GRAVITATION/FRAMERATE;
        m_posY+= m_vectorBall.second/FRAMERATE;
    }

    if( m_posY == GAME_FLOOR && m_flying == true)
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
    {
        m_posX += m_vectorBall.first;
    }
    else if (m_posX + m_vectorBall.first < 0 )
    {
        m_posX = 0;
    }
    else
        m_posX = 900 - m_width;

    m_posY += m_vectorBall.second;

    if(m_posY >= GAME_FLOOR + PRECISION)
    {
        m_vectorBall.second =0;
        m_posY=GAME_FLOOR;
    }
}

/********************************************
    Player Control Function
*********************************************
    @author Arthur  @date  8/04 - 9/04
    @author Florian @date  22/03 - 10/04
*********************************************/
void Player::controlPlayerMovements(bool left)
{
    m_inDeceleration = false;

    if (left == true && m_vectorBall.first > -10)
        m_vectorBall.first -= m_moveX*ACCELERATION/FRAMERATE;
    else if ( left == false && m_vectorBall.first <10)
        m_vectorBall.first += m_moveX*ACCELERATION/FRAMERATE;
}

