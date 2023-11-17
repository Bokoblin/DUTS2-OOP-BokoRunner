/* Copyright 2018-2019 Jolivet Arthur

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

#ifndef EVENT_UTILS_H
#define EVENT_UTILS_H

#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <libs/MDC-SFML/src/components/buttons/Button.h>
#include <libs/MDC-SFML/src/components/Text.h>
#include <libs/MDC-SFML/src/components/Dialog.h>

namespace mdsf = Bokoblin::MaterialDesignComponentsForSFML;

/**
 * The EventUtils class defines simple events accessible to the application.
 *
 * @author Arthur
 * @date 30/10/2018 - 13/01/19
 */
class EventUtils
{
public:
    //=== KEYBOARD CHECK METHODS
    static bool wasKeyboardLeftPressed();
    static bool wasKeyboardRightPressed();
    static bool wasKeyboardJumpPressed();
    static bool wasKeyboardContinuePressed();
    static bool wasKeyboardEscapePressed(const sf::Event& event);

    //=== EVENT BULK CHECK
    static void verifyHover(const sf::Event& event, const std::vector<mdsf::Button*>& elements);
    static void verifyClick(const sf::Event& event, const std::vector<mdsf::Button*>& elements);
    static bool wasMouseLeftPressed(const sf::Event& event);
    static bool wasMouseReleased(const sf::Event& event);
    /**@deprecated*/ static bool isMouseInside(const mdsf::Button& sprite, const sf::Event& event); //TODO: Remove once button list
    /**@deprecated*/ static bool isMouseInside(const mdsf::Text& sprite, const sf::Event& event); //TODO: Remove once button list
    /**@deprecated*/ static bool isMouseInside(const mdsf::Dialog& dialog, const sf::Event& event); //TODO: Remove once button list
private:
    //=== FUNCTION POINTERS
    typedef std::function<void(mdsf::Button*, bool value)> actionable_func_t;

    //=== METHODS
    static void verifyEvent(const sf::Event& event, const std::vector<mdsf::Button*>& elements, const actionable_func_t& func);
};

#endif
