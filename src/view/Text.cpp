#include "Text.h"
#include "../constants.h"

using namespace std;


/**
 * Constructs a Text with a description
 * @author Arthur
 * @date 21/12/16
 *
 * @param description the description used to parse text string
 */
Text::Text(std::string description) : m_description{description}
{
    m_font.loadFromFile(ROBOTO_REGULAR_FONT);
    setFont(m_font);
    setColor(sf::Color::White);
    m_isVisible = true;
}

/**
 * Constructs a Text with a description and a visible state
 * @author Arthur
 * @date 21/12/16
 *
 * @param description the description used to parse text string
 * @param isVisible defines if text is visible at instantiation
 */
Text::Text(std::string description, bool isVisible) : m_description{description}
{
    m_font.loadFromFile(ROBOTO_REGULAR_FONT);
    setFont(m_font);
    setColor(sf::Color::White);
    m_isVisible = isVisible;
}

//=== Getters

std::string Text::getDescription() const { return m_description; }
bool Text::isVisible() const { return m_isVisible; }

//=== Setters

void Text::setDescription(std::string description) { m_description = description; }
void Text::setTextFont(const sf::Font &font, unsigned int charSize, sf::Color color)
{
    sf::Text::setFont(font);
    sf::Text::setCharacterSize(charSize);
    sf::Text::setColor(color);
}
void Text::setVisible(bool on) { m_isVisible = on; }
void Text::setPositionSelfCentered(double x, double y) {
    setPosition( (float)(x-getGlobalBounds().width/2), (float)(y-getGlobalBounds().height/2) );
}
void Text::setStringFromInt(int value) {
    setString(to_string(value));
}

/**
 * Checks if a point of given coordinates
 * is contained in the text
 * @author Arthur
 * @date 23/12/16
 */
bool Text::contains(float posX, float posY) const
{
    return getGlobalBounds().contains(sf::Vector2f(posX, posY));
}

/**
 * Draws text on the window
 * @author Arthur
 * @date 02/01/17
 */
void Text::draw(sf::RenderWindow *window) const
{
    if ( isVisible() )
    {
        window->draw(*this);
    }
}
