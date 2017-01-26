#include "Coin.h"

using namespace std;

/**
 * Constructs a coin with
 * coordinates, a size, a moving vector
 * @author Arthur  
 * @date 19/03/16
 *
 * @param x the x position
 * @param y the y position
 * @param w the width
 * @param h the height
 * @param mvX the x moving direction
 * @param mvY the y moving direction
 */
Coin::Coin(float x, float y, float w, float h, float mvX, float mvY) :
    MovableElement(x, y, w, h, mvX, mvY)
{
    m_elementType = COIN;
}


/**
 * Destructor
 * @author Arthur
 * @date 19/03/16
 */
Coin::~Coin()
{}


/**
 * Coin Moving
 * @author Arthur
 * @date 19/03/16
 */
void Coin::move()
{
    m_posX += m_moveX;
    m_posY += m_moveY;
}
