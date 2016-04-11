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

#ifndef MENU_H
#define MENU_H

#include "View.h"

/********************************************
    Constant Variables
********************************************/
const std::string TITLE_IMAGE = "Images/title.png";
const std::string BUTTONS_IMAGE = "Images/buttons.png";


/********************************************
    Menu Class
*********************************************
    @author Arthur  @date 26/03 - 02/04
*********************************************/
class Menu : public View
{
public:
    //=== CTORs / DTORs
    Menu(float w, float h, sf::RenderWindow *window);
    virtual ~Menu();

    //=== METHODS
    virtual void synchronize() override;
    virtual void draw() const override;
    virtual void loadImages() override;
    virtual bool treatEvents() override;

private:
    //=== ATTRIBUTES

    //Textures
    sf::Texture m_farBackgroundTexture;
    sf::Texture m_nearBackgroundTexture;
    sf::Texture m_titleTexture;
    sf::Texture m_playButtonTexture;
    sf::Texture m_quitButtonTexture;

    //Graphic Elements
    SlidingBackground *m_farBackground;
    SlidingBackground *m_nearBackground;
    GraphicElement *m_titleGraphic;
    Button *m_playButtonGraphic;
    Button *m_quitButtonGraphic;
};

#endif // MENU_H
