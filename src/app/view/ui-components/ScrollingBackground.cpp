#include "ScrollingBackground.h"

//------------------------------------------------
//          CONSTRUCTORS / DESTRUCTOR
//------------------------------------------------

/**
 * Constructs a scrolling background with
 * a size, a scrolling speed and a background image.
 *
 * @param width a width
 * @param height a height
 * @param scrollingSpeed a scrolling speed
 * @param image an image to scroll
 *
 * @author Arthur, Florian
 * @date 3/03/16 - 29/12/17
 */
ScrollingBackground::ScrollingBackground(float width, float height, float scrollingSpeed, const std::string& image) :
        Sprite(width, height), m_scrollingSpeed{scrollingSpeed}
{
    m_left = new mdsf::Sprite(0, 0, width, height);
    m_left->loadAndApplyTextureFromImageFile(image);
    m_right = new mdsf::Sprite(width, 0, width, height);
    m_right->loadAndApplyTextureFromImageFile(image);

    m_left->resize(width, height);
    m_right->resize(width, height);
}


/**
 * Destructor
 * @author Arthur
 * @date 5/03/16 - 15/04/16
 */
ScrollingBackground::~ScrollingBackground()
{
    delete m_left;
    delete m_right;
}


//------------------------------------------------
//          GETTERS
//------------------------------------------------

float ScrollingBackground::getWidth() const
{return m_left->getWidth() + m_right->getWidth();}

float ScrollingBackground::getHeight() const
{return m_left->getHeight() + m_right->getHeight();}

sf::Vector2f ScrollingBackground::getLeftPosition() const
{return m_left->getPosition();}

float ScrollingBackground::getSeparationPositionX(unsigned int screenWidth) const
{
    /*
     * Depending on the current displaying (left-right or right-left),
     * it returns the visible separation position
     */
    if (m_left->getX() >= -(4.0f * screenWidth / 3) && m_left->getX() <= screenWidth) {
        return m_left->getX() + m_left->getLocalBounds().width;
    } else {
        return m_right->getX() + m_right->getLocalBounds().width;
    }
}


//------------------------------------------------
//          SETTERS
//------------------------------------------------

void ScrollingBackground::setScrollingSpeed(float speed)
{m_scrollingSpeed = speed;}

void ScrollingBackground::setPositions(float x, float y)
{
    m_left->setPosition(x, y);
    m_right->setPosition(x + m_left->getWidth(), y);
}


//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * Synchronizes the scrolling background
 * @author Arthur
 * @date 3/03/16 - 29/12/17
 */
void ScrollingBackground::sync()
{
    Sprite::sync();

    m_left->setPosition(m_left->getX() - m_scrollingSpeed, m_left->getY());
    m_right->setPosition(m_right->getX() - m_scrollingSpeed, m_right->getY());

    if (m_left->getX() + m_left->getWidth() < 0) {
        m_left->setPosition(0, 0);
        m_right->setPosition(m_left->getWidth(), 0);
    }

    applyColor();
}


/**
 * Draws the scrolling background on the window
 *
 * @param window the window
 *
 * @author Arthur
 * @date 3/03/16 - 03/04/16
 */
void ScrollingBackground::draw(sf::RenderWindow* window) const
{
    window->draw(*m_left);
    window->draw(*m_right);
}


/**
 * Resizing function
 *
 * @param width the new width
 * @param height the new height
 *
 * @author Arthur
 * @date 30/04/16
 */
void ScrollingBackground::resize(float width, float height)
{
    m_left->resize(width, height);
    m_right->resize(width, height);
}


/**
 * Checks if a point of given coordinates is contained
 * inside this element
 *
 * @param x the x-axis of position to check
 * @param y the y-axis of position to check
 *
 * @author Arthur
 * @date 30/04/16
 */
bool ScrollingBackground::contains(float x, float y) const
{
    return m_left->contains(x, y) || m_right->contains(x, y);
}


/**
 * Applies light and alpha values to color
 *
 * @author Arthur
 * @date 24/12/17 - 13/09/18
 */
void ScrollingBackground::applyColor()
{
    m_left->setColor(sf::Color(static_cast<sf::Uint8>(getColor().r * 0.01f * m_light),
                               static_cast<sf::Uint8>(getColor().g * 0.01f * m_light),
                               static_cast<sf::Uint8>(getColor().b * 0.01f * m_light),
                               m_alpha));
    m_right->setColor(sf::Color(static_cast<sf::Uint8>(getColor().r * 0.01f * m_light),
                                static_cast<sf::Uint8>(getColor().g * 0.01f * m_light),
                                static_cast<sf::Uint8>(getColor().b * 0.01f * m_light),
                                m_alpha));
}

/**
 * Loads a texture from an image file
 * and applies it to the SlidingBackground's left and right sprites on loading success
 *
 * @param imageFile the source file
 *
 * @author Arthur
 * @date 02/01/17
 */
void ScrollingBackground::loadAndApplyTextureFromImageFile(const std::string& imageFile)
{
    m_left->loadAndApplyTextureFromImageFile(imageFile);
    m_right->loadAndApplyTextureFromImageFile(imageFile);
}
