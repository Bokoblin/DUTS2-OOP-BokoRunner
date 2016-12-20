#include "Enemy.h"

/**
 * Parameterized Constructor
 * @author Arthur
 * @date 13/03
 */
Enemy::Enemy(float x, float y, float w, float h, float mvX, float mvY) :
        MovableElement(x, y, w, h, mvX, mvY)
{
    chooseEnemyType();
}


/**
 * Destructor
 * @author Arthur
 * @date 13/03
 */
Enemy::~Enemy() {}


/**
 * Enemy Moving
 * @author Arthur
 * @date 13/03
 */
void Enemy::move()
{
    m_posX += m_moveX;
    m_posY += m_moveY;
}

/**
 * Next Enemy Choosing with the following probabilities : \n
 *    1-55 : STANDARD  ~55% \n
 *   56-80 : TOTEM     ~25% \n
 *  81-100 : BLOCK     ~20%
 * @author Arthur
 * @date 13/03 - 05/04
 */
void Enemy::chooseEnemyType()
{
    int result = 1+ rand()%100;

    if (result <= 55)
    {
        m_elementType = STANDARD_ENEMY;
        m_width = 30;
        m_height = 30;
    }
    else if (result <= 80)
    {
        m_elementType = TOTEM_ENEMY;
        m_width = 30;
        m_height = 90;
    }
    else
    {
        m_elementType = BLOCK_ENEMY;
        m_width = 50;
        m_height = 50;
    }
}
