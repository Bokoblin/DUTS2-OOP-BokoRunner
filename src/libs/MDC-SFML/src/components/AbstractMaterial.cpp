#include "AbstractMaterial.h"
#include "../../../../app/model/utils/StringHash.h"

namespace Bokoblin
{
namespace MaterialDesignComponentsForSFML
{
//------------------------------------------------
//          CONSTRUCTORS / DESTRUCTOR
//------------------------------------------------
/**
 * Constructs with a size and an optional image
 *
 * @param width the width
 * @param height the height
 * @param depth the element depth
 *
 * @author Arthur
 * @date 21/02/2016 - 28/06/2020
 */
AbstractMaterial::AbstractMaterial(float width, float height, int depth) :
        m_alpha{255}, m_light{100}, m_depth{depth},
        m_initialSize{sf::Vector2f(width, height)}, m_size{sf::Vector2f(width, height)},
        m_fillColor{sf::Color(0, 0, 0, 0)},
        m_outlineColor{sf::Color(0, 0, 0, 0)}
{
    m_states[VISIBLE] = true;
    m_states[NEED_RESIZE] = false;
}

/**
 * Copy Constructor
 *
 * @param other another button object to copy
 *
 * @author Arthur, Florian
 * @date 25/02/2016 - 28/06/2020
 */
AbstractMaterial::AbstractMaterial(AbstractMaterial const& other) :
        m_alpha{other.m_alpha}, m_light{other.m_light}, m_depth{other.m_depth},
        m_initialSize{other.m_initialSize},
        m_size{other.m_size},
        m_fillColor{other.m_fillColor},
        m_states{other.m_states} {}

//------------------------------------------------
//          GETTERS
//------------------------------------------------
bool AbstractMaterial::isVisible() const { return m_states.at(VISIBLE); }
int AbstractMaterial::getAlpha() const { return m_alpha; }
int AbstractMaterial::getLight() const { return m_light; }
int AbstractMaterial::getDepth() const { return m_depth; }
const sf::Vector2f& AbstractMaterial::getOriginalSize() const { return m_initialSize; }
const sf::Vector2f& AbstractMaterial::getSize() { return m_size; }
float AbstractMaterial::getWidth() const { return m_size.x; }
float AbstractMaterial::getHeight() const { return m_size.y; }


//------------------------------------------------
//          GETTERS
//------------------------------------------------
void AbstractMaterial::setVisible(bool visible) { m_states[VISIBLE] = visible; }
void AbstractMaterial::setAlpha(int value, Color::Modifier modifier)
{
    int alpha = m_alpha;
    switch (modifier) {
        case Color::REPL:
            alpha = value;
            break;
        case Color::INCR:
            alpha += value;
            break;
        case Color::DECR:
        default:
            alpha -= value;
    }
    m_alpha = static_cast<sf::Uint8>((alpha < 0) ? 0 : (alpha > 255) ? 255 : alpha);
}

void AbstractMaterial::setLight(int value, Color::Modifier modifier)
{
    int light = m_light;
    switch (modifier) {
        case Color::REPL:
            light = value;
            break;
        case Color::INCR:
            light += value;
            break;
        case Color::DECR:
        default:
            light -= value;
    }
    m_light = static_cast<sf::Uint8>((light < 0) ? 0 : (light > 100) ? 100 : light);
}

void AbstractMaterial::setFillColor(const sf::Color& color) { applyColor(m_fillColor, color); }

void AbstractMaterial::setOutlineColor(const sf::Color& color) { applyColor(m_fillColor, color); }

//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * Resizes the sprite using scaling.
 * This base function is only kept for compatibility and
 * does not have any real effect
 *
 * @param width the new width (optional)
 * @param height the new height (optional)
 *
 * @author Arthur
 * @date 05/07/2020
 */
void AbstractMaterial::resize(const sf::Vector2f& size)
{
    //NOTE: Kept for compatibility but will disappear with sized textures
    //TODO: remove if not useful as redefined (abstract)
    Config::printError("No effect function");
    m_size = size;
}

/**
 * Resizes the sprite using scaling.
 * The function is implemented such that
 * if one of the param has default value: same size is applied,
 * if both have default value: resizing is triggered on the current size
 *
 * @param width the new width (optional)
 * @param height the new height (optional)
 *
 * @author Arthur
 * @date 22/02/2016 - 05/07/2020
 */
void AbstractMaterial::resize(float width, float height)
{
    if (width == -1 && height == -1) {
        resize(m_size);
    } else if (width == -1) {
        resize(sf::Vector2f(height, height));
    } else if (height == -1) {
        resize(sf::Vector2f(width, width));
    } else {
        resize(sf::Vector2f(width, height));
    }
}

/**
 * Applies light and alpha values to color
 *
 * @param target the target color
 * @param target the source color
 *
 * @author Arthur
 * @date 24/12/2017 - 28/06/2020
 */
void AbstractMaterial:: applyColor(sf::Color target, sf::Color source)
{
    target = sf::Color(static_cast<sf::Uint8>(source.r * 0.01f * m_light),
                       static_cast<sf::Uint8>(source.g * 0.01f * m_light),
                       static_cast<sf::Uint8>(source.b * 0.01f * m_light),
                       m_alpha);
}

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin
