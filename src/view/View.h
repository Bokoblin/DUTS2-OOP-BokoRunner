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

#ifndef VIEW_H
#define VIEW_H

#include "../model/GameModel.h"
#include "TextHandler.h"
#include "SlidingBackground.h"
#include "AnimatedGraphicElement.h"
#include "Button.h"
#include <SFML/Audio.hpp>

#define ENV_CENTERED sf::Vector2i( (sf::VideoMode::getDesktopMode().width - m_width)/2, \
				(sf::VideoMode::getDesktopMode().height - m_height)/2 )
#define MINE_GREY_COLOR sf::Color(51, 51, 51, 255)
#define FORM_BUTTONS_SIZE 30,30
#define MOUSE_LEFT_PRESSED_EVENT event.type == sf::Event::MouseButtonPressed \
                && event.mouseButton.button == sf::Mouse::Left
#define MOUSE_POSITION event.mouseButton.x, event.mouseButton.y


/**
 * View Abstract Class
 * @author Arthur, Florian
 * @date 21/02/16 - 23/10/16
 */
class View
{
    public:
        //=== CTORs / DTORs
        View(float w, float h, sf::RenderWindow *window, TextHandler *text );
        View( const View& myView ) = delete;
        virtual ~View();

        //=== SETTERS
        void setModel(Model *model);

        //=== METHODS
        virtual void loadImages()=0;
        virtual void synchronize()=0;
        virtual void draw() const =0;
        virtual bool treatEvents()=0;

    protected:
        //=== ATTRIBUTES
        float m_width, m_height;
        sf::RenderWindow *m_window;
        TextHandler *m_textHandler;
        Model *m_model;
};

#endif
