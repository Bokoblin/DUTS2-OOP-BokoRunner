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
}

//=== Getters

std::string Text::getDescription() const {
    return m_description;
}


//=== Getters

void Text::setDescription(std::string description) {
    m_description = description;
}
void Text::setPositionSelfCentered(double x, double y) {
    setPosition( (float)(x-getGlobalBounds().width/2), (float)y );
}
void Text::setStringFromInt(int value) {
    setString(to_string(value));
}


