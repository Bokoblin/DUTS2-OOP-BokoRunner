#include "../header/Coin.h"

using namespace std;

/********************************************
    Parameterized Constructor
*********************************************
    @author Arthur  @date 19/03
*********************************************/
Coin::Coin(float x, float y, float w, float h, float mvX, float mvY) :
    MovableElement(x, y, w, h, mvX, mvY)
{
    m_elementType = 4;
    m_life = 1;
}


/********************************************
    Destructor
*********************************************
    @author Arthur  @date 19/03
*********************************************/
Coin::~Coin()
{}


/********************************************
    Coin Moving
*********************************************
    @author Arthur  @date 19/03
*********************************************/
void Coin::move()
{
    m_posX += m_moveX;
    m_posY += m_moveY;
}
