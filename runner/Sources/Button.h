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

#ifndef BUTTON_H
#define BUTTON_H

#include "GraphicElement.h"

/********************************************
    Button Class
*********************************************
    @author Arthur  @date 6/04 - 22/05
*********************************************/
class Button : public GraphicElement
{
public:
    //=== CTORs / DTORs
    Button(const std::vector<sf::IntRect> & clipRects,
            sf::Texture &image, float x, float y, float w, float h, bool isRadio);
    Button(Button const& elementACopier);
    virtual ~Button();

    //=== GETTERS
    bool getDisabledState() const;

    //=== SETTERS
    void setPressedState(bool state);
    void setActivatedState(bool state);
    void setDisabledState(bool state);
    void setClipRectArray(std::vector<sf::IntRect> array);

    //=== METHODS
    virtual void sync() override;

private:
    //=== ATTRIBUTES
    std::vector<sf::IntRect> m_clipRectsArray;
    unsigned int m_currentClipRect;
    bool m_isRadio;
    bool m_pressed;
    bool m_active;
    bool m_disabled;
};

#endif // BUTTON_H
