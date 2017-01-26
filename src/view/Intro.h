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

#ifndef INTRO_H
#define INTRO_H

#include "View.h"

/**
 * Intro Class
 * @author Arthur
 * @date 27/03/16 - 14/04/16
 */
class Intro : public View
{
    public:
    //=== CTORs / DTORs
    Intro(float w, float h, sf::RenderWindow *window, TextHandler *text);
    virtual ~Intro();

    //=== METHODS
    virtual void synchronize() override;
    virtual void draw() const override;
    virtual void loadImages() override;
    virtual bool treatEvents() override;

private:
    //=== ATTRIBUTES
    GraphicElement *m_introGraphic;
};

#endif