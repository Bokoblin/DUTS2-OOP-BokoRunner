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

#ifndef ABSTRACT_VIEW_H
#define ABSTRACT_VIEW_H

#include <SFML/Audio.hpp>
#include "../../libs/MDC-SFML/src/Color.h"
#include "../../libs/MDC-SFML/src/Button.h"
#include "AppColor.h"
#include "TextHandler.h"
#include "ScrollingBackground.h"
#include "AnimatedSprite.h"

/**
 * The AbstractView class provides common
 * attributes and methods that will be used
 * by its inherited classes.
 *
 * @author Arthur, Florian
 * @date 21/02/16 - 27/12/17
 */
class AbstractView
{
public:
    //=== CTORs / DTORs
    AbstractView(sf::RenderWindow *window, TextHandler *textHandler);
    AbstractView(float width, float height, sf::RenderWindow *window, TextHandler *textHandler);
    AbstractView(const AbstractView& myView) = delete;
    virtual ~AbstractView();

    //=== METHODS
    virtual void synchronize() = 0;
    virtual void draw() const = 0;
    virtual bool handleEvents(sf::Event event) = 0;

protected:
    //=== ATTRIBUTES
    float m_width, m_height;
    sf::RenderWindow *m_window;
    TextHandler *m_textHandler;

    //=== METHODS
    virtual void loadImages() = 0;
};

#endif
