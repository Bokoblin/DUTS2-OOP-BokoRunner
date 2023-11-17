/* Copyright 2019-2020 Jolivet Arthur & Laronze Florian

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
 * that is, having multiple scrolling backgrounds superposed.
 *
 * @author Arthur
 * @date 13/07/2019 - 05/07/2020
 */
class ParallaxBackground: public mdsf::AbstractMaterial, public mdsf::ISynchronizable
{
public:
    //=== CTORs / DTORs
    ParallaxBackground(float width, float height);
    ParallaxBackground(ParallaxBackground const& other) = delete;
    ~ParallaxBackground();

    //=== GETTERS
    ScrollingBackground* getBackground(unsigned int depth);

    //=== METHODS
    void sync() override;
    void setLight(int value, mdsf::Color::Modifier modifier = mdsf::Color::REPL) override;
    void addBackground(int depth, float speed, const std::string& image);

private:
    //=== METHODS
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    //=== ATTRIBUTES
    float m_width;
    float m_height;
    std::map<int, ScrollingBackground*> m_backgrounds;
};

#endif
