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
    @author Arthur  @date 11/04 - 12/04
*********************************************/
void Bonus::chooseBonusType()
{
    int result = 1 + rand()%100;

    if (result <= 45)
        m_elementType = 5;
    else if (result <= 60)
        m_elementType = 6;
    else if ( result <= 80)
        m_elementType = 7;
    else
        m_elementType = 8;
}
