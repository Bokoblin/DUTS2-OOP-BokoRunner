/* Copyright 2019 Jolivet Arthur & Laronze Florian

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

#ifndef PARALLAX_BACKGROUND_H
#define PARALLAX_BACKGROUND_H

#include <map>
#include "ScrollingBackground.h"

/**
 * @class ParallaxBackground
 * @details Provide an implementation of parallax background, 
 * that is having multiple scrolling backgrounds superposed.
 *
 * @author Arthur
 * @date 13/07/2019
 * 
 * @see ScrollingBackground
 */
class ParallaxBackground
{
public:
    //=== CTORs / DTORs
    ParallaxBackground(float width, float height);
    ParallaxBackground(ParallaxBackground const& other) = delete;
    ~ParallaxBackground();

    //=== GETTERS
    ScrollingBackground* getBackground(unsigned int depth);

    //=== METHODS
    void addBackground(int depth, float speed, const std::string& image);
    void sync();
    void draw(sf::RenderWindow* window) const;

    void setLight(int light);
    void increaseLight(int light);
    void applyColor();

private:
    //=== ATTRIBUTES
    float m_width;
    float m_height;
    std::map<int, ScrollingBackground*> m_backgrounds;
};

#endif
