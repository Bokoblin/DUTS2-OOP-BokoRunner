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
 * Constructs a Text with a description
 *
 * @param description the description used to parse text string
 *
 * @author Arthur
 * @date 21/12/16 - 03/11/17
 */
Text::Text(const string &description) : m_description{description}, m_isVisible{true}
{
    m_font.loadFromFile(Config::DEFAULT_REGULAR_FONT);
    setFont(m_font);
    setFillColor(sf::Color::White);
}

/**
 * Constructs a Text with a description and a visible state
 *
 * @param description the description used to parse text string
 * @param isVisible defines if text is visible at instantiation
 *
 * @author Arthur
 * @date 21/12/16 - 03/11/17
 */
Text::Text(const string &description, bool isVisible) : Text(description)
{
    m_isVisible = isVisible;
}


/**
 * Copy Constructor
 *
 * @param other another text object to copy
 *
 * @author Arthur
 * @date 04/01/18
 */
Text::Text(Text const& other) :
        sf::Text(other), m_font{other.m_font}, m_description{m_description}, m_isVisible{m_isVisible}
{}


//------------------------------------------------
//          GETTERS
//------------------------------------------------

float Text::getWidth() const { return getGlobalBounds().width; };
float Text::getHeight() const { return getGlobalBounds().height; };
string Text::getDescription() const { return m_description; }
bool Text::isVisible() const { return m_isVisible; }


//------------------------------------------------
//          SETTERS
//------------------------------------------------

void Text::setDescription(const string &description) { m_description = description; }
void Text::setVisible(bool visible) { m_isVisible = visible; }
void Text::setPositionSelfCentered(float x, float y) { setPosition(x - getWidth()/2, y - getHeight()/2); }
void Text::setStringFromInt(int value) { setString(std::to_string(value)); }


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
 * @date 23/12/16
 */
bool Text::contains(float x, float y) const
{
    return getGlobalBounds().contains(sf::Vector2f(x, y));
}

/**
 * Draws text on the window if visible
 *
 * @param window the app's window
 *
 * @author Arthur
 * @date 02/01/17
 */
void Text::draw(sf::RenderWindow *window) const
{
    if (isVisible())
    {
        window->draw(*this);
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
 * @date ??/??/17 - 29/12/17
 */
void Text::applyTextFont(const string &fontFileName, unsigned int charSize, sf::Color color)
{
    m_font.loadFromFile(fontFileName);
    sf::Text::setCharacterSize(charSize);
    sf::Text::setFillColor(color);
}

} //namespace MaterialDesignComponentsForSFML
} //namespace Bokoblin
