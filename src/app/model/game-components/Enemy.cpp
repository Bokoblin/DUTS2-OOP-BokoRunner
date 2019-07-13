#include "Enemy.h"

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
 *
 * @author Arthur
 * @date 13/03/2016
 */
Enemy::Enemy(float x, float y, float w, float h, float mvX, float mvY) :
        MovableElement(x, y, w, h, mvX, mvY)
{
    chooseEnemyType();
}

/**
 * @brief Destructor
 *
 * @author Arthur
 * @date 13/03/2016
 */
Enemy::~Enemy() = default;

//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * @brief Execute the move routine
 *
 * @author Arthur
 * @date 13/03/2016 - 11/07/2019
 */
void Enemy::move()
{
    m_posX -= 1;
}

/**
 * @brief Select the enemy type following probabilities
 * @details Here are the probabilities: \n
 *    1-55 : STANDARD  ~55% \n
 *   56-80 : TOTEM     ~25% \n
 *  81-100 : BLOCK     ~20%
 *
 * @author Arthur
 * @date 13/03/2016 - 13/01/2019
 */
void Enemy::chooseEnemyType()
{
    int result = RandomUtils::getUniformRandomNumber(1, 100);

    if (result <= 55) {
        m_elementType = STANDARD_ENEMY;
        m_width = 30;
        m_height = 30;
    } else if (result <= 80) {
        m_elementType = TOTEM_ENEMY;
        m_width = 30;
        m_height = 90;
    } else {
        m_elementType = BLOCK_ENEMY;
        m_width = 50;
        m_height = 50;
    }
}
