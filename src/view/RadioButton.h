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

#ifndef RADIO_BUTTON_H
#define RADIO_BUTTON_H

#include "Button.h"

/**
 * The RadioButton Class inherited from Button class
 * adds different syncing behaviours
 * a pre-configured texture with its clip rectangles
 * and a different label location than other buttons
 *
 * @author Arthur
 * @date 23/12/16 - 02/01/17
 */
class RadioButton : public Button
{
public:
    //=== CTORs / DTORs
    RadioButton(float x, float y, float w, float h);
    RadioButton(float x, float y, float width, float height, const std::string &label);
    RadioButton(const RadioButton& other);
    virtual ~RadioButton() override;

    //=== METHODS
    virtual void sync() override;
    virtual void sync(DataBase *dataBase) override;

private:
    void setRadioClipRect();
};

#endif
