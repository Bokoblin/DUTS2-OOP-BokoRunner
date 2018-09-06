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

#ifndef SLIDING_BACKGROUND_H
#define SLIDING_BACKGROUND_H

#include "libs/MDC-SFML/src/Sprite.h"

namespace mdsf = Bokoblin::MaterialDesignComponentsForSFML;

/**
 * The SlidingBackground class inherits mdsf::GraphicElement.
 * It defines two Sprite side by side to make an infinite sliding effect.
 *
 * @author Arthur, Florian
 * @date 3/03/16 - 10/02/18
 */
class ScrollingBackground: public mdsf::Sprite
{
public:
    //=== CTORs / DTORs
    ScrollingBackground(float width, float height, float scrollingSpeed, const std::string& image);
    ScrollingBackground(ScrollingBackground const& other) = delete;
    ~ScrollingBackground() override;

    //=== GETTERS
    float getWidth() const override;
    float getHeight() const override;
    sf::Vector2f getLeftPosition() const;
    float getSeparationPositionX(unsigned int screenWidth) const;

    //=== SETTERS
    void setScrollingSpeed(float speed);
    void setPositions(float x, float y);

    //=== METHODS
    void sync() override;
    void draw(sf::RenderWindow* window) const override;

    void resize(float width, float height) override;
    bool contains(float x, float y) const override;
    void applyColor() override;

    void loadAndApplyTextureFromImageFile(const std::string& imageFile) override;

private:
    //=== ATTRIBUTES
    mdsf::Sprite* m_left, * m_right;
    float m_scrollingSpeed;
};

#endif
