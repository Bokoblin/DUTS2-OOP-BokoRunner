#include "Enemy.h"

/********************************************
    Parameterized Constructor
*********************************************
    @author Arthur  @date 13/03
*********************************************/
Enemy::Enemy(float x, float y, float w, float h, float mvX, float mvY) :
    MovableElement(x, y, w, h, mvX, mvY)
{
    chooseEnemyType();
}


/********************************************
    Destructor
*********************************************
    @author Arthur  @date 13/03
*********************************************/
Enemy::~Enemy()
{}


/********************************************
    Enemy Moving
*********************************************
    @author Arthur  @date 13/03
*********************************************/
void Enemy::move()
{
    m_posX += m_moveX;
    m_posY += m_moveY;
}

/********************************************
    Next Enemy Type Choosing
*********************************************
    @author Arthur  @date 13/03 - 05/04
*********************************************/
void Enemy::chooseEnemyType()
{
    int result = 1+ rand()%100;

    if (result <= 55)
    {
        m_elementType = 1;
        m_width = 30;
        m_height = 30;
    }

    else if (result <= 80)
    {
        m_elementType = 2;
        m_width = 30;
        m_height = 90;
    }

    else
    {
        m_elementType = 3;
        m_width = 50;
        m_height = 50;
    }
}
