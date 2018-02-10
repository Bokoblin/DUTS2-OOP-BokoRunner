/* Copyright 2016-2018 Jolivet Arthur & Laronze Florian

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef VIEW_DEFINITIONS_H
#define VIEW_DEFINITIONS_H

/**
 * Provides pre-processor definitions to view classes
 *
 * @author Arthur
 * @date 16/04/17 - 25/01/18
 */

//FIXME: remove some definitions (consts in-class, custom objects), add other lost ones

//=== SFML DEFINITIONS
#define MOUSE_LEFT_PRESSED_EVENT event.type == sf::Event::MouseButtonPressed \
                && event.mouseButton.button == sf::Mouse::Left
#define MOUSE_POSITION event.mouseButton.x, event.mouseButton.y

#define KEYBOARD_LEFT  (sf::Keyboard::isKeyPressed(sf::Keyboard::A) \
                       || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
#define KEYBOARD_RIGHT (sf::Keyboard::isKeyPressed(sf::Keyboard::D) \
                       || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
#define KEYBOARD_JUMP  (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) \
                       || sf::Keyboard::isKeyPressed(sf::Keyboard::W))


//=== OTHER DEFINITIONS
#define TITLE_TEXT_X (m_height/12)
#define FORM_BUTTONS_SIZE 30, 30
#define RADIO_DIAMETER 25
#define INDICATOR_DIAMETER 22
#define PAUSE_BUTTONS_SIZE 25, 25
#define RAISED_BUTTON_DEFAULT 0, 101, 150, 36
#define RAISED_BUTTON_PRESSED 151, 101, 150, 36

#endif
