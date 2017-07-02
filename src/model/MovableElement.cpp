#include "MovableElement.h"

using namespace std;

/**
 * Constructs from an inherited class with
 * coordinates, a size, a moving vector
 * @author Arthur, Florian
 * @date 23/02/16 - 09/04/16
 *
 * @param x the x position
 * @param y the y position
 * @param w the width
 * @param h the height
 * @param mvX the x moving direction
 * @param mvY the y moving direction
 */
MovableElement::MovableElement(float x, float y, float w, float h, float mvX, float mvY) :
    m_posX{x}, m_posY{y}, m_width{w}, m_height{h}, m_moveX{mvX}, m_moveY{mvY},
    m_isColliding{false}, m_elementType{UNDEFINED}
{}


/**
 * Destructor
 * @author Arthur
 * @date 23/02/16
 */
MovableElement::~MovableElement() {}


//=== Getters

float MovableElement::getPosX()  const { return m_posX;  }
float MovableElement::getPosY()  const { return m_posY;  }
float MovableElement::getWidth() const { return m_width; }
float MovableElement::getHeight()const { return m_height;}
MovableElementType MovableElement::getType() const { return m_elementType; }
bool MovableElement::isColliding() const { return m_isColliding; }


//=== Setters

void MovableElement::setMoveX(float mvX) { m_moveX = mvX;}
void MovableElement::setMoveY(float mvY) { m_moveY = mvY;}
void MovableElement::setColliding(bool on) { m_isColliding = on;}


/**
 * Checks if a position belongs to an element
 * @author Arthur
 * @date 08/03/16 - 09/04/16
 *
 * @param posX the other element x-position
 * @param posY the other element y-position
 * @return a boolean indicating if position is in element
 */
bool MovableElement::contains(float posX, float posY) const
{
    float  maxX = m_posX + m_width;
    float  maxY = m_posY + m_height;

    return (posX >= m_posX) && (posX < maxX) && (posY >= m_posY) && (posY < maxY);
}


/**
 * Determines if elements are colliding
 *
 * Note : element's origin corresponds to left-bottom point
 *
 * @author Arthur
 * @date 02/04/16 - 20/12/16
 *
 * @param other the other element
 * @return a boolean indicating if elements are colliding
 */
bool MovableElement::collision(const MovableElement& other) const
{
    float leftA, leftB;
    float rightA, rightB;
    float topA, topB;
    float bottomA, bottomB;

    leftA = m_posX;
    rightA = m_posX + m_width;
    topA = m_posY - m_height;
    bottomA = m_posY;

    leftB = other.m_posX;
    rightB = other.m_posX + other.m_width;
    topB = other.m_posY - other.m_height;
    bottomB = other.m_posY;

    return bottomA >= topB && topA <= bottomB && rightA >= leftB && leftA <= rightB;
}
