#include "Bonus.h"

/**
 * Constructs a bonus with
 * coordinates, a size, a moving vector
 * @author Arthur
 * @date 11/04/16
 *
 * @param x the x position
 * @param y the y position
 * @param w the width
 * @param h the height
 * @param mvX the x moving direction
 * @param mvY the y moving direction
 */
Bonus::Bonus(float x, float y, float w, float h, float mvX, float mvY) :
    MovableElement(x, y, w, h, mvX, mvY)
{
    chooseBonusType();
}


/**
 * Destructor
 * @author Arthur
 * @date 11/04/16
 */
Bonus::~Bonus() {}


/**
 * Bonus Moving
 * @author Arthur
 * @date 11/04/16
 */
void Bonus::move()
{
    m_posX += m_moveX;
    m_posY += m_moveY;
}


/**
 * Next Bonus Choosing under the following probabilities : \n
 *  1-30 : PV+    ~30% \n
 * 31-50 : MEGA   ~20% \n
 * 51-65 : FLY    ~15% \n
 * 66-75 : SLOW   ~10% \n
 * 76-100: SHIELD ~25%
 *
 * @author Arthur
 * @date 11/04/16 - 21/05/16
 */
void Bonus::chooseBonusType()
{
    int result = 1 + rand()%100;

    if (result <= 30)
        m_elementType = PV_PLUS_BONUS;
    else if (result <= 50)
        m_elementType = MEGA_BONUS;
    else if ( result <= 65)
        m_elementType = FLY_BONUS;
    else if ( result <= 75)
        m_elementType = SLOW_SPEED_BONUS;
    else
        m_elementType = SHIELD_BONUS;
}