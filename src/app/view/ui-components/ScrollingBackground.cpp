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
        AbstractMaterial(width, height), m_scrollingSpeed{scrollingSpeed}
{
    m_left = new mdsf::Image(0, 0, width, height); //FIXME: not an abstract material it wants
    m_left->loadAndApplyTextureFromFile(image);
    m_right = new mdsf::Image(width, 0, width, height);
    m_right->loadAndApplyTextureFromFile(image);

    //m_left->resize(width, height);
    //m_right->resize(width, height);
    m_size = sf::Vector2f(m_left->getWidth() + m_right->getWidth(),
                          m_left->getHeight() + m_right->getHeight());
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

//const sf::Vector2f& ScrollingBackground::getSize()
//{
//    m_size = sf::Vector2f(m_left->getWidth() + m_right->getWidth(),
//                                  m_left->getHeight() + m_right->getHeight());
//    return m_computedSize;
//}

//------------------------------------------------
//          SETTERS
//------------------------------------------------
void ScrollingBackground::setScrollingSpeed(float speed) { m_scrollingSpeed = speed; }

void ScrollingBackground::setPosition(float x, float y)
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
    m_left->setFillColor(m_fillColor);
    m_left->setOutlineColor(m_outlineColor);

    m_left->setPosition(m_left->getX() - m_scrollingSpeed, m_left->getY());
    m_right->setPosition(m_right->getX() - m_scrollingSpeed, m_right->getY());

    if (m_left->getX() + m_left->getWidth() < 0) {
        m_left->setPosition(0, 0);
        m_right->setPosition(m_left->getWidth(), 0);
    }

    //applyColor();
}

/**
 * Draws the scrolling background on the window
 *
 * @param window the window
 *
 * @author Arthur
 * @date 3/03/2016 - 05/07/2020
 */
void ScrollingBackground::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(*m_left, states);
    target.draw(*m_right, states);
}

/**
* Resizes the background image using scaling.
*
* @param size a scalar defining the size to apply
*
* @author Arthur
* @date 30/04/2016 - 05/07/2020
*/
void ScrollingBackground::resize(const sf::Vector2f &size)
{
    m_left->resize(size);
    m_right->resize(size);
}


///**
// * Checks if a point of given coordinates is contained
// * inside this element
// *
// * @param x the x-axis of position to check
// * @param y the y-axis of position to check
// *
// * @author Arthur
// * @date 30/04/16
// */
//bool ScrollingBackground::contains(float x, float y) const
//{
//    return m_left->contains(x, y) || m_right->contains(x, y);
//}

/**
 * Calculate the central position of the scrolling background
 * @note Depending on the current displaying (left-right or right-left),
 * it returns the visible central position
 *
 * @author Arthur
 * @date 16/04/2017 - 05/07/2020
 */
sf::Vector2f ScrollingBackground::calculateCenter(float screenWidth) const
{
    if (m_left->getX() >= -(4.0f * screenWidth / 3) && m_left->getX() <= screenWidth) {
        return {m_left->getX() + m_left->getWidth(), m_left->getHeight() / 2};
    } else {
        return {m_right->getX() + m_right->getWidth(), m_left->getHeight() / 2};
    }
}

/**
 * Loads a texture from an image file
 * and applies it to the SlidingBackground's left and right sprites on loading success
 *
 * @param file the source file
 *
 * @author Arthur
 * @date 02/01/2017 - 05/07/2020
 */
void ScrollingBackground::loadAndApplyTextureFromFile(const std::string& file, const sf::IntRect& area)
{
    m_left->loadAndApplyTextureFromFile(file, area);
    m_right->loadAndApplyTextureFromFile(file, area);
}

float ScrollingBackground::getX() const
{
    return m_left->getX();
}

float ScrollingBackground::getY() const
{
    return m_right->getY();
}

bool ScrollingBackground::contains(const sf::Vector2f& position) const
{
    return false; //FIXME: won't use I think
}

void ScrollingBackground::setOrigin(float x, float y) {
    m_left->setOrigin(x, y);
}


