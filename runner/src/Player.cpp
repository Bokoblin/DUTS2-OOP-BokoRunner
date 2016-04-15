#include "../header/Player.h"

using namespace std;

/********************************************
    Parameterized Constructor
*********************************************
    @author Arthur  @date 22/02 - 11/04
    @author Florian @date 22/02 - 15/04
*********************************************/
Player::Player(float x, float y, float w, float h, float mvX, float mvY):
    MovableElement(x, y, w, h, mvX, mvY), m_state{0}, m_gravitation{20.0},
    m_acceleration{18.0}, m_jumping{false}, m_flying{false}, m_inDeceleration{false}
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
int Player::getState() const { return m_state; }
bool Player::getFlyingState() const { return m_flying; }
bool Player::getJumpState() const { return m_jumping; }
bool Player::getDecelerationState() const { return m_inDeceleration; }
std::pair<float,float> Player::getVector() const { return m_vectorBall; }


/********************************************
    Setters
*********************************************
    @author Arthur  @date 08/04 - 11/04
    @author Florian @date 17/03 - 6/04
*********************************************/
void Player::setFlyingState(bool etat) { m_flying = etat; }
void Player::setJumpState(bool etat) {  m_jumping = etat; }
void Player::setDecelerationState(bool etat) {  m_inDeceleration = etat; }

void Player::setLife(int new_life)
{
    m_life = new_life;
    if ( m_life > 100 ) m_life = 100;
    else if ( m_life < 0 ) m_life = 0;
}


/********************************************
    Player Move Function
*********************************************
    @author Florian @date  12/03 - 15/04
*********************************************/
void Player::move()
{
    m_flying = m_width < GAME_FLOOR;

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
        m_vectorBall.second = -m_acceleration*m_gravitation/FRAMERATE;
        m_posY+= m_vectorBall.second/FRAMERATE;
    }

    if(m_flying)
    {
        m_vectorBall.second += m_gravitation/FRAMERATE;
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


/********************************************
    Change player's state
*********************************************
    @author Arthur  @date  11/04
*********************************************/
void Player::changeState(int state)
{
    if ( state == 0) //normal
    {
        cout << "Player has taken the NORMAL type , it's not very effective" << endl;
        m_width = 30;
        m_height = 30;
        m_state = 0;
        m_gravitation = 20.0;
        m_acceleration = 18.0;
    }
    else if ( state == 1) //mega
    {
        cout << "MegaEvolutionnnnnnnnn !" << endl;
        m_width = 70;
        m_height = 70;
        m_state = 1;
        m_gravitation = 20.0;
        m_acceleration = 18.0;
    }
    else if ( state == 2) //fly
    {
        cout << "Player has taken the FLY type, it's super effective !" << endl;
        m_width = 30;
        m_height = 30;
        m_state = 2;
        m_gravitation = 5.0;
        m_acceleration = 70.0;
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
        m_vectorBall.first -= m_moveX*m_acceleration/FRAMERATE;
    else if ( left == false && m_vectorBall.first <10)
        m_vectorBall.first += m_moveX*m_acceleration/FRAMERATE;
}

