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

#ifndef GRAPHICELEMENT_H
#define GRAPHICELEMENT_H

#include <SFML/Graphics.hpp>

/********************************************
    GraphicElement Class
*********************************************
    @author Arthur  @date 21/02 - 6/04
    @author Florian @date 21/02 - 2/03
*********************************************/
class GraphicElement : public sf::Sprite
{
public:
    //=== CTORs / DTORs
    GraphicElement(sf::Texture &image, float x, float y, float w, float h);
    GraphicElement( float w, float h);
    GraphicElement(GraphicElement const& elementACopier);
    ~GraphicElement();

    //=== METHODS
    virtual void sync();
    virtual void draw(sf::RenderWindow *window)const;
    virtual void resize(float w, float h);

protected:
    //=== ATTRIBUTES
    float m_width;
    float m_height;
};

#endif // GRAPHICELEMENT_H
