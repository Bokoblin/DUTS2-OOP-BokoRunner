/* Copyright 2016 Jolivet Arthur & Laronze Florian

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

#ifndef _VIEW_H
#define _VIEW_H

#include "Text.h"
#include "SlidingBackground.h"
#include "AnimatedGraphicElement.h"
#include "Button.h"
#include <SFML/Audio.hpp>

#define ENVIRONMENT_CENTER sf::Vector2i( (sf::VideoMode::getDesktopMode().width - m_width)/2, \
				(sf::VideoMode::getDesktopMode().height - m_height)/2 )
#define GREY_BG_COLOR sf::Color(51, 51, 51, 255)
#define FORM_BUTTONS_SIZE 30,30
#define MOUSE_LEFT_PRESSED_EVENT event.type == sf::Event::MouseButtonPressed &&           event.mouseButton.button == sf::Mouse::Left
#define IS_POINTED getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))

/********************************************
    Constant Variables
********************************************/
const int SCREEN_BPP = 32;
const std::string APP_TITLE = "Boko Runner";
const std::string IUT_LOGO_IMAGE = "Images/logo_iut.png";
const std::string DEFAULT_FAR_HILL_BACKGROUND = "Images/background/hill_far.png";
const std::string DEFAULT_NEAR_HILL_BACKGROUND = "Images/background/hill_near.png";
const std::string DEFAULT_FAR_PLAIN_BACKGROUND = "Images/background/plain_far.png";
const std::string DEFAULT_NEAR_PLAIN_BACKGROUND = "Images/background/plain_near.png";
const std::string DEFAULT_FAR_T1_BACKGROUND = "Images/background/t1_far.png";
const std::string DEFAULT_NEAR_T1_BACKGROUND = "Images/background/t1_near.png";
const std::string DEFAULT_FAR_T2_BACKGROUND = "Images/background/t2_far.png";
const std::string DEFAULT_NEAR_T2_BACKGROUND = "Images/background/t2_near.png";
const std::string INDICATOR_IMAGE = "Images/indicator_buttons.png";
const std::string RADIO_BUTTONS_IMAGE = "Images/radio_buttons.png";
const std::string MENU_RECT_BUTTONS_IMAGE = "Images/rect_buttons.png";
const std::string FORM_BUTTONS_IMAGE = "Images/menu_buttons.png";
const std::string BONUS_IMAGE = "Images/bonus.png";

class Model;

/********************************************
    View Abstract Class
*********************************************
    @author Arthur  @date 21/02 - 18/05
    @author Florian @date 21/02 - 3/03
*********************************************/
class View
{
    public:
        //=== CTORs / DTORs
        View( float w, float h, sf::RenderWindow *window, Text *text );
        View( const View& myView ) = delete;
        ~View();

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
        Text *m_text;
        Model *m_model;
};

#endif
