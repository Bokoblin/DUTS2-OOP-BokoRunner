/* Copyright 2016-2017 Jolivet Arthur & Laronze Florian

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

#ifndef DEFINITIONS_H
#define DEFINITIONS_H

/**
 * Provides pre-processor definitions to view classes
 * @author Arthur
 * @date 16/04/17
 */

//=== COLORS DEFINITIONS
#define MATERIAL_TEAL_COLOR sf::Color(0, 150, 136, 255)
#define MINE_GREY_COLOR sf::Color(51, 51, 51, 255)
#define GOLD_COLOR sf::Color(255, 204, 0, 255)
#define ENEMY_BLUE_COLOR sf::Color(0, 232, 209, 255)
#define END_GREY_COLOR sf::Color(86, 103, 97, 255)

//=== SFML DEFINITIONS
#define ENVIRONMENT_CENTER sf::Vector2i((sf::VideoMode::getDesktopMode().width - m_width)/2, \
				(sf::VideoMode::getDesktopMode().height - m_height)/2)
#define MOUSE_LEFT_PRESSED_EVENT event.type == sf::Event::MouseButtonPressed \
                && event.mouseButton.button == sf::Mouse::Left
#define MOUSE_POSITION event.mouseButton.x, event.mouseButton.y

#define KEYBOARD_LEFT  (sf::Keyboard::isKeyPressed(sf::Keyboard::A) \
                       || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
#define KEYBOARD_RIGHT (sf::Keyboard::isKeyPressed(sf::Keyboard::D) \
                       || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
#define KEYBOARD_JUMP  (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) \
                       || sf::Keyboard::isKeyPressed(sf::Keyboard::W))

#define RED_BUTTON_UP sf::IntRect(0, 100, 150, 40)
#define GREEN_BUTTON_UP sf::IntRect(0, 178, 150, 43)
#define GREEN_BUTTON_DOWN sf::IntRect(151, 179, 150, 40)

//=== OTHER DEFINITIONS
#define TITLE_TEXT_X m_height/12
#define FORM_BUTTONS_SIZE 30, 30
#define RADIOS_MARGIN 50
#define RADIO_BUTTONS_SIZE 26, 26
#define INDICATOR_BUTTONS_SIZE 22, 22

#endif
