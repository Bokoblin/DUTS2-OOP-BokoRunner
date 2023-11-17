#include "Text.h"

using std::string;

namespace Bokoblin
{
namespace MaterialDesignComponentsForSFML
{
//------------------------------------------------
//          CONSTRUCTORS / DESTRUCTOR
//------------------------------------------------
/**
 * Constructs a Text with provided parameters
 *
 * @param description the description used to parse text string
 * @param isVisible defines if text is visible at instantiation
 *
 * @author Arthur
 * @date 21/12/2016 - 28/06/2020
 */
Text::Text(const string& description, bool isVisible) :
        AbstractMaterial(0, 0, 5), m_description{description}
{
    m_states[VISIBLE] = isVisible;
    m_fillColor = sf::Color::White;
    m_font.loadFromFile(Config::DEFAULT_REGULAR_FONT);
    m_text.setFont(m_font);
}

/**
 * Copy Constructor
 *
 * @param other another text object to copy
 *
 * @author Arthur
 * @date 04/01/2018 - 28/06/2020
 */
Text::Text(Text const& other) :
        AbstractMaterial(other),
        m_text{other.m_text}, m_font{other.m_font}, m_description{other.m_description} {}

//------------------------------------------------
//          GETTERS
//------------------------------------------------
float Text::getX() const { return m_text.getPosition().x; }
float Text::getY() const { return m_text.getPosition().y; }
float Text::getWidth() const { return m_text.getGlobalBounds().width / m_text.getScale().x; }
float Text::getHeight() const { return m_text.getGlobalBounds().height / m_text.getScale().y; }
string Text::getDescription() const { return m_description; }
unsigned int Text::getCharacterSize() const { return m_text.getCharacterSize(); }

//------------------------------------------------
//          SETTERS
//------------------------------------------------
void Text::setDescription(const string& description) { m_description = description; }

void Text::setPositionSelfCentered(float x, float y) { m_text.setPosition(x - getWidth() / 2, y - getHeight() / 2); }

void Text::setStringFromInt(int value) { m_text.setString(std::to_string(value)); }

void Text::setFont(const sf::Font& font) { m_text.setFont(font); }

void Text::setCharacterSize(unsigned int size) { m_text.setCharacterSize(size); }
void Text::setStyle(int style) { m_text.setStyle(style); }

void Text::setString(const string& content) { m_text.setString(content); }

void Text::setUtf8String(const string& content) { m_text.setString(sf::String::fromUtf8(content.begin(), content.end())); }

//------------------------------------------------
//          METHODS
//------------------------------------------------
/**
 * Checks if a point of given coordinates
 *
 * @param x the x-axis coordinate
 * @param y the y-axis coordinate
 *
 * is contained in the text
 * @author Arthur
 * @date 23/12/2016
 */
bool Text::contains(const sf::Vector2f& position) const
{
    return m_text.getGlobalBounds().contains(position);
}

/**
 * Draws text on the window if visible
 *
 * @param window the app's window
 *
 * @author Arthur
 * @date 02/01/2017
 */
void Text::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (isVisible()) {
        target.draw(m_text, states);
    }
}

/**
 * Applies a font with a character size and a color to a text
 *
 * @param fontFileName the new font's file name
 * @param charSize the new character size
 * @param color the new color
 *
 * @author Arthur
 * @date 07/01/2017 - 28/06/2020
 */
void Text::applyTextFont(const string& fontFileName, unsigned int charSize, const sf::Color& color)
{
    m_font.loadFromFile(fontFileName);
    m_text.setCharacterSize(charSize);
    m_text.setFillColor(color);
}

void Text::setPosition(float x, float y)
{
    m_text.setPosition(x, y);
}

void Text::setOrigin(float x, float y)
{
    m_text.setOrigin(x, y);
}

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin
