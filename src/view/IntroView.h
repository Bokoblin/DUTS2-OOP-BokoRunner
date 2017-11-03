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

#include "AbstractView.h"
#include "../model/IntroModel.h"
#include "../utils/definitions.h"

/**
 * The IntroView class displays
 * a little banner at app startup
 * @author Arthur
 * @date 27/03/16 - 02/11/17
 */
class IntroView : public AbstractView
{
    public:
    //=== CTORs / DTORs
    IntroView(sf::RenderWindow *window, TextHandler *textHandler, IntroModel *introModel);
    virtual ~IntroView();

    //=== METHODS
    virtual void synchronize() override;
    virtual void draw() const override;
    virtual void loadImages() override;
    virtual bool treatEvents(sf::Event event) override;

private:
    //=== ATTRIBUTES
    IntroModel *m_intro;
    GraphicElement *m_introGraphic;
};

//TODO: Quitting animation + renaming

#endif