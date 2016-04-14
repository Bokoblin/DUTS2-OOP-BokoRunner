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

#include <sstream>
#define MOUSE_POSITION sf::Vector2f(event.mouseButton.x, event.mouseButton.y)

/********************************************
    Constant Variables
********************************************/
const std::string BACKGROUND_IMAGE_1 = "Images/city_1.png";
const std::string BACKGROUND_IMAGE_2 = "Images/city_2.png";

class Model;

/********************************************
    View Abstract Class
*********************************************
    @author Arthur  @date 21/02 - 03/04
    @author Florian @date 21/02 - 3/03
*********************************************/
class View
{
public:
    //=== CTORs / DTORs
    View( float w, float h, sf::RenderWindow *window, Text *text );
    View( const View& myView ) = delete;
    ~View();

    //=== GETTERS
    sf::RenderWindow* getWindow();

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
