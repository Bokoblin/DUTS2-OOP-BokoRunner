#include "Button.h"

using std::string;

namespace Bokoblin
{
namespace MaterialDesignComponentsForSFML
{
//------------------------------------------------
//          CONSTRUCTORS / DESTRUCTOR
//------------------------------------------------
//TODO: add clip rect parameter for allowing non-states clips to regroup images
// (to introduce with image DB (filename + origin + original size))

/**
 * @brief Constructs a button with coordinates,
 * a size, a texture and an image rectangle clip
 *
 * @param x the x-axis coordinate
 * @param y the y-axis coordinate
 * @param width the width
 * @param height the height
 * @param description the label's description (optional)
 * @param textureFile the button texture image (optional)
 *
 * @author Arthur
 * @date 06/04/2016 - 28/06/2020
 */
Button::Button(float x, float y, float width, float height,
               const LabelPosition& labelPosition, const string& description, const string& textureFile) :
        AbstractTexturedMaterial(width, height, textureFile),
        m_label{description}, m_labelPosition{labelPosition}
{
    m_buttonSprite.setPosition(x, y);
    m_states[CLICKED] = false;
    m_states[ENABLED] = true;
    m_states[HOVERED] = false;
    m_states[PRESSED] = false;
    m_states[NEED_RESIZE] = true;
    m_states[NEED_LABEL_SYNC] = true;
    m_font.loadFromFile(Config::DEFAULT_CONDENSED_FONT);
    m_label.setFont(m_font);
    m_label.setFillColor(sf::Color::White);
    m_label.setCharacterSize(DEFAULT_CHAR_SIZE);
}

/**
 * @brief Copy Constructor
 *
 * @param other another button object to copy
 *
 * @author Arthur
 * @date 06/04/2016 - 28/06/2020
 */
Button::Button(Button const& other) :
        AbstractTexturedMaterial(other),
        m_font{other.m_font}, m_label{other.m_label}, m_labelPosition{other.m_labelPosition}
{
    m_buttonSprite.setPosition(other.m_buttonSprite.getPosition());
    m_buttonSprite.setTexture(*other.m_buttonSprite.getTexture(), true); //NOTE: Can be problematic
    m_buttonSprite.setOrigin(other.m_buttonSprite.getOrigin());
    m_buttonSprite.setColor(other.m_buttonSprite.getColor());
}

//------------------------------------------------
//          GETTERS
//------------------------------------------------
bool Button::isClicked() const { return m_states.at(CLICKED); }
bool Button::isEnabled() const { return m_states.at(ENABLED); }
bool Button::isHovered() const { return m_states.at(HOVERED); }
bool Button::isPressed() const { return m_states.at(PRESSED); }
float Button::getX() const { return m_buttonSprite.getPosition().x; }
float Button::getY() const { return m_buttonSprite.getPosition().y; }

//------------------------------------------------
//          SETTERS
//------------------------------------------------
void Button::setClicked(bool value) { m_states[CLICKED] = value; }
void Button::setEnabled(bool value) { m_states[ENABLED] = value; }
void Button::setHovered(bool value) { m_states[HOVERED] = value; }
void Button::setPressed(bool value) { m_states[PRESSED] = value; }
void Button::setLabelPosition(const LabelPosition& labelPosition) { m_labelPosition = labelPosition; }
void Button::setLabelDescription(const std::string& description) { m_label.setDescription(description); }

//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * @brief Checks if a point of given coordinates is contained
 * in the button or its label
 *
 * @param x the x-axis coordinate
 * @param y the y-axis coordinate
 *
 * @author Arthur
 * @date 23/12/2016 - 05/07/2020
 */
bool Button::contains(const sf::Vector2f& position) const
{
    return isEnabled() && isVisible()
            && (m_buttonSprite.getGlobalBounds().contains(position) || m_label.contains(position));
}

/**
 * Resizes the button using sprite scaling
 *
 * @param size the new size
 *
 * @author Arthur
 * @date 28/06/2020
 */
void Button::resize(const sf::Vector2f& size)
{
    float width_factor = size.x / getOriginalSize().x;
    float height_factor = size.y / getOriginalSize().y;
    m_buttonSprite.setScale(width_factor, height_factor);
    m_size = size;
}
void Button::resize(float width, float height)
{
    //TODO
}

/**
 * @brief Synchronizes button sprite with a color modifier
 * and a scaling if needed
 *
 * @author Arthur
 * @date 06/04/2016 - 28/06/2020
 */
void Button::sync()
{
    m_buttonSprite.setColor(m_fillColor);

    if (m_states.at(NEED_RESIZE)) {
        resize(getSize());
        m_states[NEED_RESIZE] = false;
    }

    if (m_states.at(NEED_LABEL_SYNC)) {
        syncLabelPosition();
        m_states[NEED_LABEL_SYNC] = false;
    }
}

/**
 * @brief Retrieves the button's label text
 * @details Also syncs the label position as it's content as changed
 *
 * @param func the function used to retrieve the string given a label
 *
 * @author Arthur
 * @date 23/12/2016 - 14/01/2019
 */
void Button::retrieveLabel(const label_retrieval_func_t& func)
{
    if (!m_label.getDescription().empty()) {
        string utf8_string = func(m_label.getDescription());
        m_label.setUtf8String(utf8_string);
    }

    syncLabelPosition();
}

/**
 * @brief Sync the button's label position
 *
 * @author Arthur
 * @date 23/12/2016 - 04/01/2018
 */
void Button::syncLabelPosition()
{
    if (!m_label.getDescription().empty()) {
        switch (m_labelPosition) {
            case TOP:
                m_label.setPositionSelfCentered(getX() + getSize().x / 2, getY() - getSize().y / 2);
                m_label.setOrigin(0, m_label.getSize().y / 2);
                break;
            case RIGHT:
                m_label.setPosition(getX() + getSize().x + HORIZONTAL_LABEL_MARGIN, getY() + getSize().y / 2 - 7);
                m_label.setOrigin(0, m_label.getSize().y / 2);
                break;
            case BOTTOM:
                m_label.setPositionSelfCentered(getX() + getSize().x / 2, getY() + getSize().y + 50);
                m_label.setOrigin(0, m_label.getSize().y / 2);
                break;
            case LEFT:
                m_label.setPosition((getX() - HORIZONTAL_LABEL_MARGIN), getY() + getSize().y / 2 - 7);
                m_label.setOrigin(m_label.getSize().x, m_label.getSize().y / 2);
                break;
            case CENTER:
                m_label.setPositionSelfCentered(getX() + getSize().x / 2, getY() + getSize().y / 2 + 2);
                m_label.setOrigin(0, m_label.getSize().y / 2);
                break;
        }
    }
}

/**
 * @brief Draws the button and its label if visible
 *
 * @param target the drawing target
 * @param states the rendering states
 *
 * @author Arthur
 * @date 23/12/2016 - 02/01/2018
 */
void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (isVisible()) {
        target.draw(m_buttonSprite, states);
        target.draw(m_label, states);
    }
}

void Button::processTextureLoading(const string& file)
{
    AbstractTexturedMaterial::processTextureLoading(file);
    m_buttonSprite.setTexture(m_texture);
}

void Button::resize(float size)
{
    resize(size, size);
}

void Button::setOrigin(float x, float y)
{
    m_buttonSprite.setOrigin(x, y);
}

void Button::setPosition(float x, float y)
{
    m_buttonSprite.setPosition(x, y);
}

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin
