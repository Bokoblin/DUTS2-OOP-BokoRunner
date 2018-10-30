#include "EventUtils.h"

//------------------------------------------------
//          METHODS
//------------------------------------------------

/**
 * Tests if one of the keys defining a left action was pressed
 * @return true, if action was triggered
 *
 * @author Arthur
 * @date 30/10/18
 */
bool EventUtils::wasKeyboardLeftPressed()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
}


/**
 * Tests if one of the keys defining a right action was pressed
 * @return true, if action was triggered 
 *
 * @author Arthur
 * @date 30/10/18
 */
bool EventUtils::wasKeyboardRightPressed()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
}


/**
 * Tests if one of the keys defining a jump action was pressed
 * @return true, if action was triggered 
 *
 * @author Arthur
 * @date 30/10/18
 */
bool EventUtils::wasKeyboardJumpPressed()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W);
}


/**
 * Tests if one of the keys defining a continue action was pressed
 * @return true, if action was triggered 
 *
 * @author Arthur
 * @date 30/10/18
 */
bool EventUtils::wasKeyboardContinuePressed()
{
    return sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Return);
}


/**
 * Tests if one of the keys defining a cancel/escape action was pressed
 * @return true, if action was triggered 
 *
 * @author Arthur
 * @date 30/10/18
 */
bool EventUtils::wasKeyboardEscapePressed(sf::Event event)
{
    return event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape;
}


/**
 * Tests if the mouse left button was pressed
 * @return true, if action was triggered 
 *
 * @author Arthur
 * @date 30/10/18
 */
bool EventUtils::wasMouseLeftPressed(sf::Event event)
{
    return event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left;
}


/**
 * Tests if the mouse was released
 * @return true, if action was triggered 
 *
 * @author Arthur
 * @date 30/10/18
 */
bool EventUtils::wasMouseReleased(sf::Event event)
{
    return event.type == sf::Event::MouseButtonReleased;
}


/**
 * Tests if the mouse is inside a sprite area
 * @return true, if action was triggered 
 *
 * @author Arthur
 * @date 30/10/18
 */
bool EventUtils::isMouseInside(const mdsf::Sprite& sprite, sf::Event event)
{
    return sprite.contains(event.mouseButton.x, event.mouseButton.y);
}


/**
 * Tests if the mouse is inside a text area
 * @return true, if action was triggered 
 *
 * @author Arthur
 * @date 30/10/18
 */
bool EventUtils::isMouseInside(const mdsf::Text& text, sf::Event event)
{
    return text.contains(event.mouseButton.x, event.mouseButton.y);
}
