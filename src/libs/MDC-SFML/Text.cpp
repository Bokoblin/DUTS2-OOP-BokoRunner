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
 * @author Arthur
 * @date 21/12/16 - 03/11/17
 *
 * @param description the description used to parse text string
 */
Text::Text(const string &description) : m_description{description}, m_isVisible{true}
{
    m_font.loadFromFile(Config::DEFAULT_REGULAR_FONT);
    setFont(m_font);
    setFillColor(sf::Color::White);
}

/**
 * Constructs a Text with a description and a visible state
 * @author Arthur
 * @date 21/12/16 - 03/11/17
 *
 * @param description the description used to parse text string
 * @param isVisible defines if text is visible at instantiation
 */
Text::Text(const string &description, bool isVisible) : Text(description)
{
    m_isVisible = isVisible;
}


//------------------------------------------------
//          GETTERS
//------------------------------------------------

string Text::getDescription() const { return m_description; }
bool Text::isVisible() const { return m_isVisible; }


//------------------------------------------------
//          SETTERS
//------------------------------------------------

void Text::setDescription(const string &description) { m_description = description; }
void Text::setVisible(bool on) { m_isVisible = on; }
void Text::setPositionSelfCentered(double x, double y) { setPosition(
            (float)(x - getGlobalBounds().width / 2), //TODO : getWidth()
            (float)(y - getGlobalBounds().height / 2));
}
void Text::setStringFromInt(int value) { setString(std::to_string(value)); }


//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * Checks if a point of given coordinates
 * is contained in the text
 * @author Arthur
 * @date 23/12/16
 *
 * @param posX the text x position
 * @param posY the text y position
 */
bool Text::contains(float posX, float posY) const
{
    return getGlobalBounds().contains(sf::Vector2f(posX, posY));
}

/**
 * Draws text on the window
 * @author Arthur
 * @date 02/01/17
 *
 * @param window the app's window
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
