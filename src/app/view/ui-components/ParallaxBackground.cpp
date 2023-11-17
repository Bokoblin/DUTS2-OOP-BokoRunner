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
 * @date 13/07/2019 - 05/07/2020
 */
ParallaxBackground::ParallaxBackground(float width, float height) :
        mdsf::AbstractMaterial(width, height) {}

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
 * @date 13/07/2019 - 05/07/2020
 */
void ParallaxBackground::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto background: m_backgrounds) {
        target.draw(*background.second, states);
    }
}

/**
 * @brief Apply the light setting to every elements
 *
 * @author Arthur
 * @date 13/07/2019 - 05/07/2020
 */
void ParallaxBackground::setLight(int value, mdsf::Color::Modifier modifier)
{
    for (auto background: m_backgrounds) {
        background.second->setLight(value, modifier);
    }
}
