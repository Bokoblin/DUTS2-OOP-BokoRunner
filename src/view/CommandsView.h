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

#ifndef COMMANDS_VIEW_H
#define COMMANDS_VIEW_H

#include "View.h"
#include "../model/Commands.h"


/**
 * The CommandsView class displays
 * game's command
 * @author Arthur
 * @date 24/01/17 - 10/04/17
 */
class CommandsView : public View
{
public:
    //=== CTORs / DTORs
    CommandsView(float w, float h, sf::RenderWindow *window, TextHandler *textHandler);
    virtual ~CommandsView();

    //=== SETTERS
    void setCommandsModel(Commands *model);

    //=== METHODS
    virtual void synchronize() override;
    virtual void draw() const override;
    virtual void loadImages() override;
    virtual bool treatEvents() override;
    bool treatEvents( sf::Event event );

private:
    //=== ATTRIBUTES
    Commands *m_commands;

    //Graphic Elements
    GraphicElement *m_commandSprite;
    Button *m_homeFormButton;
};


#endif
