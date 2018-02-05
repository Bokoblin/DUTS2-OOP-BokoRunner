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

#ifndef COMMANDS_VIEW_H
#define COMMANDS_VIEW_H

#include "AbstractView.h"
#include "app/model/CommandsModel.h"
#include "app/utils/definitions.h"

/**
 * The CommandsView class inherits AbstractView.
 * It is the view counterpart of the class CommandsModel.
 * It handles the commands screen's rendering.
 *
 * @author Arthur
 * @date 24/01/17 - 05/02/18
 */
class CommandsView : public AbstractView
{
public:
    //=== CTORs / DTORs
    CommandsView(sf::RenderWindow *window, AppTextManager *textManager, CommandsModel *commandsModel);
    ~CommandsView() override;

    //=== METHODS
    void synchronize() override;
    void draw() const override;
    bool handleEvents(sf::Event event) override;

private:
    //=== ATTRIBUTES
    CommandsModel *m_commands;
    mdsf::Button *m_homeFormButton;

    //=== METHODS
    void loadSprites() override;
};

#endif
