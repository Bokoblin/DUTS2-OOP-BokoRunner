#include "Coin.h"

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
 * @date 19/03/2016
 */
Coin::Coin(float x, float y, float w, float h, float mvX, float mvY) :
        MovableElement(x, y, w, h, mvX, mvY)
{
    m_elementType = COIN;
}

/**
 * @brief Destructor
 *
 * @author Arthur
 * @date 19/03/2016
 */
Coin::~Coin() = default;

//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * @brief Execute the move routine
 *
 * @author Arthur
 * @date 19/03/2016 - 11/07/2019
 */
void Coin::move()
{
    m_posX -= 1;
}
