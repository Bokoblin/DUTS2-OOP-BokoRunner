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

#ifndef ANIMATEDGRAPHICELEMENT_H
#define ANIMATEDGRAPHICELEMENT_H

#include "GraphicElement.h"
#include <chrono>

/********************************************
    AnimatedGraphicElement Class
*********************************************
    @author Arthur  @date 3/03 - 22/05
*********************************************/
class AnimatedGraphicElement : public GraphicElement
{
public:
    //=== CTORs / DTORs
    AnimatedGraphicElement(sf::Texture &image, float x, float y, float w, float h,
            const std::vector<sf::IntRect> & clipRects);
    AnimatedGraphicElement( const AnimatedGraphicElement& other);
    virtual ~AnimatedGraphicElement();

    //=== SETTERS
    void setClipRectArray(std::vector<sf::IntRect> array);

    //=== METHODS
    virtual void sync() override;

private:
    //=== ATTRIBUTES
    std::vector<sf::IntRect> m_clipRectsArray;
    unsigned int m_currentClipRect;
    std::chrono::system_clock::time_point m_lastAnimationTime;
};

#endif // ANIMATEDGRAPHICELEMENT_H
