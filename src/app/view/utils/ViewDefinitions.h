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
 * @date 16/04/17 - 13/09/18
 */

//FIXME: remove some definitions here (custom objects, utils shortcut functions in MDSF),...

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
#define DEFAULT_HOME_SIZE 50

#endif
