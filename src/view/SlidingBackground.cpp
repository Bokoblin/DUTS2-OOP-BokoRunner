#include "SlidingBackground.h"

/**
 * Parameterized Constructor
 * @author Arthur, Florian
 * @date 3/03/16 - 02/01/17
 */
SlidingBackground::SlidingBackground(float width, float height, float speed, std::string image) :
    GraphicElement(width, height), m_speed{speed}, m_alpha{255}
{
    m_left = new GraphicElement(0, 0, width, height);
    m_left->setTextureFromImage(image);
    m_right = new GraphicElement(width, 0, width, height);
    m_right->setTextureFromImage(image);
}


/**
 * Destructor
 * @author Arthur
 * @date 5/03/16 - 15/04/16
 */
SlidingBackground::~SlidingBackground()
{
    delete m_left;
    delete m_right;
}


//=== Getters

int SlidingBackground::getAlpha() const { return m_alpha; }
sf::Vector2f SlidingBackground::getPosition() const
{
    return m_left->getPosition();
}

float SlidingBackground::getSeparationPositionX() const
{
    if ( m_left->getPosition().x >= -1200 && m_left->getPosition().x <= 900) //left is on screen
        return m_left->getPosition().x + m_left->getLocalBounds().width;
    else
        return m_right->getPosition().x + m_right->getLocalBounds().width;
}


//=== Setters

void SlidingBackground::setSpeed(float speed) { m_speed = speed; }

void SlidingBackground::setAlpha(int alpha)
{
    if (alpha < 0)
        m_alpha = 0;
    else if (alpha > 255)
        m_alpha = 255;
    else
        m_alpha = (sf::Uint8) alpha;
}

void SlidingBackground::setPosition(float x, float y)
{
    m_left->setPosition(x, y);
    m_right->setPosition(x + m_width, y);
}


/**
 * Synchronization Function
 * @author Arthur
 * @date 3/03/16 - 7/05/16
 */
void SlidingBackground::sync()
{
    m_left->setPosition(m_left->getPosition().x - m_speed, m_left->getPosition().y);
    m_right->setPosition(m_right->getPosition().x - m_speed, m_right->getPosition().y);

    if ( m_left->getPosition().x + m_width < 0 )
    {
        m_left->setPosition(0, 0);
        m_right->setPosition(m_width, 0);
    }

    m_left->setColor(sf::Color(255, 255, 255, m_alpha));
    m_right->setColor(sf::Color(255, 255, 255, m_alpha));
}


/**
 * Drawing Function
 * @author Arthur
 * @date 3/03/16 - 03/04/16
 */
void SlidingBackground::draw(sf::RenderWindow *window) const
{
    window->draw(*m_left);
    window->draw(*m_right);
}


/**
 * Resizing function
 * @author Arthur
 * @date 30/04/16
 */
void SlidingBackground::resize(float width, float height)
{
    m_left->resize(width, height);
    m_right->resize(width, height);
}


/**
 * Decrease alpha function
 * @author Arthur
 * @date 7/05/16 - 15/04/17
 */
void SlidingBackground::decreaseAlpha(int level)
{
    setAlpha(getAlpha() - level);
}

/**
 * Increase alpha function
 * @author Arthur
 * @date 7/05/16 - 15/04/17
 */
void SlidingBackground::increaseAlpha(int level)
{
    setAlpha(getAlpha() + level);
}


/**
 * Sets the SlidingBackground's texture from an image
 * @author Arthur
 * @date 02/01/17
 */
void SlidingBackground::setTextureFromImage(const std::string &image)
{
    m_left->setTextureFromImage(image);
    m_right->setTextureFromImage(image);
}


