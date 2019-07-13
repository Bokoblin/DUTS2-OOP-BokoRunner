#include "ParallaxBackground.h"

//------------------------------------------------
//          CONSTRUCTORS / DESTRUCTOR
//------------------------------------------------

/**
 * @brief Constructor
 *
 * @param width a width
 * @param height a height
 *
 * @author Arthur
 * @date 13/07/2019
 */
ParallaxBackground::ParallaxBackground(float width, float height) :
        m_width{width}, m_height{height} {}

/**
 * @brief Destructor
 *
 * @author Arthur
 * @date 13/07/2019
 */
ParallaxBackground::~ParallaxBackground()
{
    for (auto background: m_backgrounds) {
        delete background.second;
    }
}

//------------------------------------------------
//          GETTERS
//------------------------------------------------

ScrollingBackground* ParallaxBackground::getBackground(unsigned int depth)
{
    return m_backgrounds.at(depth);
}

//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * @brief Add a new background to the parallax
 * @warning The depth value must be unique
 *
 * @param depth the background depth (higher is closer)
 * @param speed the background speed
 * @param image the background image
 *
 * @author Arthur
 * @date 13/07/2019
 */
void ParallaxBackground::addBackground(int depth, float speed, const std::string& image)
{
    m_backgrounds[depth] = new ScrollingBackground(m_width, m_height, speed, image);
}

/**
 * Synchronizes the scrolling background
 *
 * @author Arthur
 * @date 13/07/2019
 */
void ParallaxBackground::sync()
{
    for (auto background: m_backgrounds) {
        background.second->sync();
    }
}

/**
 * Draws the scrolling background on the window
 *
 * @param window the window
 *
 * @author Arthur
 * @date 13/07/2019
 */
void ParallaxBackground::draw(sf::RenderWindow* window) const
{
    for (auto background: m_backgrounds) {
        background.second->draw(window);
    }
}

/**
 * @brief Apply the light setting to every elements
 *
 * @author Arthur
 * @date 13/07/2019
 */
void ParallaxBackground::setLight(int light)
{
    for (auto background: m_backgrounds) {
        background.second->setLight(light);
    }
}

/**
 * @brief Increase the light setting for every elements
 *
 * @author Arthur
 * @date 13/07/2019
 */
void ParallaxBackground::increaseLight(int light)
{
    for (auto background: m_backgrounds) {
        background.second->increaseLight(light);
    }
}

/**
 * @brief Apply light and alpha values to color of every elements
 *
 * @author Arthur
 * @date 13/07/2019
 */
void ParallaxBackground::applyColor()
{
    for (auto background: m_backgrounds) {
        background.second->applyColor();
    }
}
