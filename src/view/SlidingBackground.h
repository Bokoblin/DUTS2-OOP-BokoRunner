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

#ifndef SLIDING_BACKGROUND_H
#define SLIDING_BACKGROUND_H

#include "GraphicElement.h"


/**
 * SlidingBackground Class
 * @author Arthur, Florian
 * @date 3/03 - 7/05
 */
class SlidingBackground : public GraphicElement
{
public:
    //=== CTORs / DTORs
    SlidingBackground(sf::Texture &image, float w, float h, float speed);
    SlidingBackground(SlidingBackground const& element) = delete;
    virtual ~SlidingBackground();

    //=== METHODS
    virtual void sync() override;
    virtual void draw(sf::RenderWindow *window) const override;
    virtual void resize(float w, float h) override;
    void decreaseAlpha(int level);
    void increaseAlpha(int level);

    //=== GETTERS
    int getAlpha() const;
    sf::Vector2f getPosition() const;
    float getSeparationPositionX() const;

    //=== SETTERS
    void setSpeed(float speed);
    void setPosition(float x, float y);
    void setAlpha(sf::Uint8 alpha);

private:
    //=== ATTRIBUTES
    GraphicElement *m_left, *m_right;
    float m_speed;
    sf::Uint8 m_alpha;

};

#endif