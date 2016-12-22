#include "Text.h"

using namespace std;

/**
 * Parameterized Constructor
 * @author Arthur
 * @date 21/12
 */
Text::Text(string description) : m_description{description}
{
    setColor(sf::Color::White);
    m_isVisible = true;
}

Text::Text(string description, bool isVisible) : m_description{description}
{
    setColor(sf::Color::White);
    m_isVisible = isVisible;
}

//=== Getters

std::string Text::getDescription() const {
    return m_description;
}
bool Text::isVisible() const {
    return m_isVisible;
}

//=== Setters

void Text::setDescription(std::string description) {
    m_description = description;
}
void Text::setPositionSelfCentered(double x, double y) {
    setPosition( (float)(x-getGlobalBounds().width/2), (float)y );
}
void Text::setStringFromInt(int value) {
    setString(to_string(value));
}
void Text::setVisible(bool on) {
    m_isVisible = on;
}




