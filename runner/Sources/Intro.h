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

#ifndef INTRO_H
#define INTRO_H

#include "View.h"

/********************************************
    Constant Variables
********************************************/
const std::string INTRO_IMAGE = "Images/intro.png";


/********************************************
    Intro Class
*********************************************
    @author Arthur  @date 27/03 - 14/04
*********************************************/
class Intro : public View
{
    public:
    //=== CTORs / DTORs
    Intro(float w, float h, sf::RenderWindow *window, Text *text);
    virtual ~Intro();

    //=== METHODS
    virtual void synchronize() override;
    virtual void draw() const override;
    virtual void loadImages() override;
    virtual bool treatEvents() override;

private:
    //=== ATTRIBUTES
    sf::Texture m_introTexture;
    GraphicElement *m_introGraphic;
};

#endif // INTRO_H
