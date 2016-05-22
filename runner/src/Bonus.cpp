#include "../header/Bonus.h"

/********************************************
    Parameterized Constructor
*********************************************
    @author Arthur  @date 11/04
*********************************************/
Bonus::Bonus(float x, float y, float w, float h, float mvX, float mvY) :
    MovableElement(x, y, w, h, mvX, mvY)
{
    chooseBonusType();
}


/********************************************
    Destructor
*********************************************
    @author Arthur  @date 11/04
*********************************************/
Bonus::~Bonus()
{}


/********************************************
    Bonus Moving
*********************************************
    @author Arthur  @date 11/04
*********************************************/
void Bonus::move()
{
    m_posX += m_moveX;
    m_posY += m_moveY;
}

/********************************************
    Next Bonus Type Choosing
*********************************************
    @author Arthur  @date 11/04 - 21/05
*********************************************/
void Bonus::chooseBonusType()
{
    int result = 1 + rand()%100;

    if (result <= 30)
        m_elementType = PVPLUSBONUS;
    else if (result <= 50)
        m_elementType = MEGABONUS;
    else if ( result <= 65)
        m_elementType = FLYBONUS;
    else if ( result <= 75)
        m_elementType = SLOWSPEEDBONUS;
    else
        m_elementType = SHIELDBONUS;

    /* Bonus percentage
    *    1-30 : PV+       ~30%
    *  31-50 : MEGA    ~20%
    *  51-65 : FLY       ~15%
    *  66-75 : SLOW   ~10%
    * 76-100: SHIELD ~25%
    */
}
