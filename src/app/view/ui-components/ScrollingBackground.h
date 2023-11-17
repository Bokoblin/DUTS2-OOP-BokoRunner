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

#include "libs/MDC-SFML/src/components/Image.h"
#include "libs/MDC-SFML/src/interfaces/ISynchronizable.h"

namespace mdsf = Bokoblin::MaterialDesignComponentsForSFML;

/**
 * @class SlidingBackground
 * @inherit mdsf::AbstractMaterial
 * @implements mdsf::IPositionable, mdsf::ISynchronizable
 * @details Defines two images scrolling side-by-side to create an infinite effect
 *
 * @author Arthur, Florian
 * @date 3/03/2016 - 05/07/2020
 */
class ScrollingBackground: public mdsf::AbstractMaterial, public mdsf::IPositionable, public mdsf::ISynchronizable
{
public:
    //=== CTORs / DTORs
    ScrollingBackground(float width, float height, float scrollingSpeed, const std::string& image);
    ScrollingBackground(ScrollingBackground const& other) = delete;
    ~ScrollingBackground() override;

    //=== GETTERS
    //const sf::Vector2f& getSize() override;
    //float getSize() const override; //TODO: will certainly be useful instead of getSize, let's see cases
    //float getHeight() const override;
    float getX() const override;
    float getY() const override;
    bool contains(const sf::Vector2f &position) const override; //FIXME: temp

    //=== SETTERS
    void setScrollingSpeed(float speed);
    void setOrigin(float x, float y) override; //FIXME: Temp for compatibility, delete if possible
    void setPosition(float x, float y) override;

    //=== METHODS
    void sync() override;

    //void resize() override;
    void resize(const sf::Vector2f& size) override;
    //void resize(float size) override;
    //void resize(float width, float height) override;
    //bool contains(float x, float y) const override;

    sf::Vector2f calculateCenter(float screenWidth) const; //Note: Don't return const ref here
    void loadAndApplyTextureFromFile(const std::string& file, const sf::IntRect& area = sf::IntRect());

private:
    //=== METHODS
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    //=== ATTRIBUTES
    mdsf::Image* m_left, * m_right; //TODO: Replace by no pointers objects
    float m_scrollingSpeed;
    sf::Vector2f m_computedSize;
};

#endif
