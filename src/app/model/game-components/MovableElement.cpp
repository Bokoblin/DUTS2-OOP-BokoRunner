#include "MovableElement.h"

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
 * @author Arthur, Florian
 * @date 23/02/2016 - 09/04/2016
 */
MovableElement::MovableElement(float x, float y, float w, float h, float mvX, float mvY) :
        m_posX{x}, m_posY{y}, m_width{w}, m_height{h}, m_moveX{mvX}, m_moveY{mvY},
        m_isColliding{false}, m_elementType{UNDEFINED}
{}


/**
 * @brief Destructor
 *
 * @author Arthur
 * @date 23/02/2016
 */
MovableElement::~MovableElement() = default;

//------------------------------------------------
//          GETTERS
//------------------------------------------------

float MovableElement::getPosX()  const { return m_posX;  }
float MovableElement::getPosY()  const { return m_posY;  }
float MovableElement::getWidth() const { return m_width; }
float MovableElement::getHeight()const { return m_height; }
MovableElementType MovableElement::getType() const { return m_elementType; }
bool MovableElement::isColliding() const { return m_isColliding; }

//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * @brief Check if a position belongs to an element
 *
 * @param x the other element x-position
 * @param y the other element y-position
 * @return a boolean indicating if position is in element
 *
 * @author Arthur
 * @date 08/03/2016 - 09/04/2016
 */
bool MovableElement::contains(float x, float y) const
{
    float maxX = m_posX + m_width;
    float maxY = m_posY + m_height;

    return (x >= m_posX) && (x < maxX) && (y >= m_posY) && (y < maxY);
}

/**
 * @brief Determine if elements are colliding
 * @note Element's origin corresponds to left-bottom point
 * @warning This function must be called by the element which is set to be deleted
 *
 * @param other the other element
 * @return a boolean indicating if elements are colliding
 *
 * @author Arthur
 * @date 02/04/2016 - 11/07/2019
 */
bool MovableElement::collide(const MovableElement& other)
{
    if (!m_isColliding) {
        float left_a, left_b;
        float right_a, right_b;
        float top_a, top_b;
        float bottom_a, bottom_b;

        left_a = m_posX;
        right_a = m_posX + m_width;
        top_a = m_posY - m_height;
        bottom_a = m_posY;

        left_b = other.m_posX;
        right_b = other.m_posX + other.m_width;
        top_b = other.m_posY - other.m_height;
        bottom_b = other.m_posY;

        m_isColliding = bottom_a >= top_b && top_a <= bottom_b && right_a >= left_b && left_a <= right_b;
    }

    return m_isColliding;
}
