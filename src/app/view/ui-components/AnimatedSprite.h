/* Copyright 2016-2020 Jolivet Arthur & Laronze Florian

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

#ifndef ANIMATED_GRAPHIC_ELEMENT_H
#define ANIMATED_GRAPHIC_ELEMENT_H

#include <chrono>
#include <libs/MDC-SFML/src/components/Image.h>

namespace mdsf = Bokoblin::MaterialDesignComponentsForSFML;

/**
 * The AnimatedSprite class adds animation to a Graphic element
 * It uses multiple clips from texture for them to change on events,
 * a timePoint of the last time the animation has changed
 * and an animation delay.
 *
 * @author Arthur
 * @date 3/03/2016 - 07/05/2020
 */
class AnimatedSprite: public mdsf::Image
{
public:
    //=== CTORs / DTORs
    AnimatedSprite(float width, float height, const std::string& image,
                   const std::vector<sf::IntRect>& clipRect);
    AnimatedSprite(float x, float y, float width, float height, const std::string& image,
                   const std::vector<sf::IntRect>& clipRect);
    AnimatedSprite(const AnimatedSprite& other);
    ~AnimatedSprite() override;

    //=== SETTERS
    void setClipRectArray(std::vector<sf::IntRect> clipRectsArray);

    //=== METHODS
    void sync() override;
    ///**@deprecated*/ void resize(float width, float height) const; //TODO: compat
    ///**@deprecated*/ void resize(float size) const; //TODO: compat

private:
    //=== ATTRIBUTES
    std::vector<sf::IntRect> m_clipRectArray;
    unsigned int m_currentClipRect;
    std::chrono::system_clock::time_point m_lastAnimationTime;

    const int ANIMATION_DELAY = 200;
};

#endif
