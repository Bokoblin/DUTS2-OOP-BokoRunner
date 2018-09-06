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

#ifndef COMMANDS_H
#define COMMANDS_H

#include "AbstractModel.h"

/**
 * The CommandsModel class inherits AbstractModel.
 * It is the model counterpart of the class CommandsView.
 * It handles the commands screen's logic
 *
 * @author Arthur
 * @date 24/01/17 - 29/12/17
 */
class CommandsModel: public AbstractModel
{
public:
    //=== CTORs / DTORs
    explicit CommandsModel(AppCore* appCore);
    ~CommandsModel() override;

    //=== METHODS
    void nextStep() override;
};

#endif
